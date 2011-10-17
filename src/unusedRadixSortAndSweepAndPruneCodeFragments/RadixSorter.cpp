#include "RadixSorter.h"

#include "../OpenCL.h"
#include "../Number.h"

#include <vector>

const cl_uint RadixSorter::KEY_MASK                   = 0xfff00000;
const cl_uint RadixSorter::INDEX_MASK                 = 0x000fffff;

const cl_uint RadixSorter::INDEX_BITS                 = 20;

const cl_uint RadixSorter::NO_BITS                    = 0;

const cl_uint RadixSorter::DO_WRITE_SUMS              = 1;
const cl_uint RadixSorter::DO_NOT_WRITE_SUMS          = 0;

const cl_uint RadixSorter::DO_WRITE_TOTAL_FALSES      = 1;
const cl_uint RadixSorter::DO_NOT_WRITE_TOTAL_FALSES  = 0;

const size_t  RadixSorter::ELEMENTS_PER_WORK_ITEM_SCAN   = 2;  // 2 because of binary tree
const size_t  RadixSorter::ELEMENTS_PER_WORK_ITEM_OTHERS = 2;  // TODO works only with 2 for now (but didn't seem faster with 4)


RadixSorter::RadixSorter(   cl_context          context,
                            cl_device_id        device,
                            cl_command_queue    queue,
                            size_t              workGroupSize,
                            size_t              count)
:   program(NULL),
    context(context),
    kernelPrefixSumScan(NULL),
    kernelAddGroupPrefix(NULL),
    kernelComputeIndexAndScatter(NULL),
    queue(queue),
    workGroupSize(workGroupSize),
    sumBuffer0(NULL),
    sumBuffer1(NULL),
    lowerElementCountsBuffer(NULL),
    totalFalsesBuffer(NULL),
    dummyBuffer(NULL),
    dummyCount(0),
    count(count),
    countRoundedUp(0),
    sumCount0(0),
    sumCount0RoundedUp(0),
    sumCount1(0),
    sumCount1RoundedUp(0),
    inputBufferIndex(0),
    outputBufferIndex(1)
{
    keyBuffers.resize(2);

    size_t elementsPerWorkGroup = workGroupSize * ELEMENTS_PER_WORK_ITEM_OTHERS;

    // Round up count to multiple of number of elements per work group

    countRoundedUp = Number::roundUpToMultiple(count, elementsPerWorkGroup);

    // Pad the buffer to this size

    bufferByteSize = countRoundedUp * sizeof(cl_int);

    // If there is more elements than we can work on with a single group
    // then we will need multiple groups and write out group results for further processing.
    //
    // Compute how many intermediate results we will get per recursion.

    sumCount0 = countRoundedUp / elementsPerWorkGroup;
    sumCount0RoundedUp = Number::roundUpToMultiple(sumCount0, elementsPerWorkGroup);
    sumBufferByteSize0 = sumCount0RoundedUp * sizeof(cl_int);

    // TODO padding required here?
    sumCount1 = sumCount0RoundedUp / elementsPerWorkGroup;
    sumCount1RoundedUp = Number::roundUpToMultiple(sumCount1, elementsPerWorkGroup);
    sumBufferByteSize1 = sumCount1RoundedUp * sizeof(cl_int);

    // Create program

    std::vector<QString> filenames;

    filenames.push_back("src/kernels/shared.cl");
    filenames.push_back("src/kernels/radixSort.cl");

    program = new Program(filenames, context, device);

    // Create kernels

    cl_int status;

    kernelPrefixSumScan = clCreateKernel(program->getProgram(), "prefixSumScan", &status);
    CL_ERROR(status);

    kernelAddGroupPrefix = clCreateKernel(program->getProgram(), "addGroupPrefix", &status);
    CL_ERROR(status);

    kernelComputeIndexAndScatter = clCreateKernel(program->getProgram(), "computeIndexAndScatter", &status);
    CL_ERROR(status);


    initBuffers();
}


RadixSorter::~RadixSorter()
{
     delete program;

     clReleaseMemObject(keyBuffers[0]);
     clReleaseMemObject(keyBuffers[1]);
     clReleaseMemObject(sumBuffer0);
     clReleaseMemObject(sumBuffer1);
     clReleaseMemObject(lowerElementCountsBuffer);
     clReleaseMemObject(dummyBuffer);
     clReleaseMemObject(totalFalsesBuffer);

     clReleaseKernel(kernelPrefixSumScan);
     clReleaseKernel(kernelAddGroupPrefix);
     clReleaseKernel(kernelComputeIndexAndScatter);
}


void RadixSorter::initBuffers()
{
    cl_int status;

    keyBuffers[0] = clCreateBuffer(context, CL_MEM_READ_WRITE, bufferByteSize, NULL, &status);
    CL_ERROR(status);

    keyBuffers[1] = clCreateBuffer(context, CL_MEM_READ_WRITE, bufferByteSize, NULL, &status);
    CL_ERROR(status);

    lowerElementCountsBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, bufferByteSize, NULL, &status);
    CL_ERROR(status);

    totalFalsesBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_uint), NULL, &status);
    CL_ERROR(status);

    if (sumCount0 > 0)
    {
        sumBuffer0 = clCreateBuffer(context, CL_MEM_READ_WRITE, sumBufferByteSize0, NULL, &status);
        CL_ERROR(status);

        if (sumCount1 > 0)
        {
            sumBuffer1 = clCreateBuffer(context, CL_MEM_READ_WRITE, sumBufferByteSize1, NULL, &status);
            CL_ERROR(status);
        }
    }

    // Seems like a bug in ATI implementation SDK 2.2 Radeon 4870 drivers 10.11 (November) prevents us
    // from passing a NULL pointer as kernel argument (the standard is a bit unclear about this though)
    // Anyway, lets initialize a dummy buffer.

    dummyBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, 1, NULL, &status);
    CL_ERROR(status);
}


cl_uint RadixSorter::getTotalFalses()
{
    cl_int status;

    cl_uint* buffer = reinterpret_cast<cl_uint*> ( clEnqueueMapBuffer(queue, totalFalsesBuffer, CL_TRUE, CL_MAP_READ, 0, sizeof(cl_uint), 0, NULL, NULL, &status) );
    CL_ERROR(status);

    cl_uint totalFalses = buffer[0];

    CL_ERROR( clEnqueueUnmapMemObject(queue, totalFalsesBuffer, buffer, 0, NULL, NULL) );

    return totalFalses;
}


std::vector<cl_uint> RadixSorter::getSums()
{
    cl_int status;

    cl_uint* buffer = reinterpret_cast<cl_uint*> ( clEnqueueMapBuffer(queue, sumBuffer0, CL_TRUE, CL_MAP_READ, 0, sumBufferByteSize0, 0, NULL, NULL, &status) );
    CL_ERROR(status);

    std::vector<cl_uint> sums(sumCount0);

    std::vector<cl_uint>::iterator iter;

    size_t i = 0;

    // TODO fast copy

    for (iter = sums.begin(); iter != sums.end(); ++iter)
    {
        (*iter) = buffer[i];

        i++;
    }

    CL_ERROR( clEnqueueUnmapMemObject(queue, sumBuffer0, buffer, 0, NULL, NULL) );

    return sums;
}


std::vector<cl_uint> RadixSorter::getLowerElementCounts()
{
    cl_int status;

    cl_uint* buffer = reinterpret_cast<cl_uint*> ( clEnqueueMapBuffer(queue, lowerElementCountsBuffer, CL_TRUE, CL_MAP_READ, 0, bufferByteSize, 0, NULL, NULL, &status) );
    CL_ERROR(status);

    std::vector<cl_uint> lowerElementCounts(count);

    std::vector<cl_uint>::iterator iter;

    size_t i = 0;

    // TODO fast copy

    for (iter = lowerElementCounts.begin(); iter != lowerElementCounts.end(); ++iter)
    {
        (*iter) = buffer[i];

        i++;
    }

    CL_ERROR( clEnqueueUnmapMemObject(queue, lowerElementCountsBuffer, buffer, 0, NULL, NULL) );

    return lowerElementCounts;
}


cl_uint RadixSorter::getInputBufferIndex()
{
    return inputBufferIndex;
}


cl_uint RadixSorter::getOutputBufferIndex()
{
    return outputBufferIndex;
}

cl_mem RadixSorter::getKeysBuffer(cl_uint index)
{
    return keyBuffers[index];
}


std::vector<cl_uint> RadixSorter::getKeys(cl_uint index)
{
    cl_int status;

    cl_uint* buffer = reinterpret_cast<cl_uint*> ( clEnqueueMapBuffer(queue, keyBuffers.at(index), CL_TRUE, CL_MAP_READ, 0, bufferByteSize, 0, NULL, NULL, &status) );
    CL_ERROR(status);

    std::vector<cl_uint> keys(count);

    std::vector<cl_uint>::iterator iter;

    size_t i = 0;

    // TODO fast copy

    for (iter = keys.begin(); iter != keys.end(); ++iter)
    {
        (*iter) = buffer[i];

        i++;
    }

    CL_ERROR( clEnqueueUnmapMemObject(queue, keyBuffers.at(index), buffer, 0, NULL, NULL) );

    return keys;
}


void RadixSorter::setKeys(const std::vector<cl_uint>& keys, cl_uint index)
{
    cl_int status;

    cl_uint* buffer = reinterpret_cast<cl_uint*> ( clEnqueueMapBuffer(queue, keyBuffers.at(index), CL_TRUE, CL_MAP_WRITE, 0, bufferByteSize, 0, NULL, NULL, &status) );
    CL_ERROR(status);

    std::vector<cl_uint>::const_iterator iter;

    size_t i = 0;

    // TODO fast copy

    for (iter = keys.begin(); iter != keys.end(); ++iter)
    {
        buffer[i] = *iter;

        i++;
    }

    CL_ERROR( clEnqueueUnmapMemObject(queue, keyBuffers.at(index), buffer, 0, NULL, NULL) );
}


void RadixSorter::logLowerElementCounts(Logger* logger)
{
    std::vector<cl_uint> counts = getLowerElementCounts();

    std::vector<cl_uint>::const_iterator iter;

    QString s;

    int i = 0;

    for (iter = counts.begin(); iter != counts.end(); ++iter)
    {
        if ((i % 10) == 0)
        {
            s += "\n";

//            break;
        }

        s += QString::number(*iter) + " ";

        i++;
    }

    logger->logInfo(s);
}


void RadixSorter::logKeys(Logger* logger, cl_uint index)
{
    std::vector<cl_uint> keys = getKeys(index);

    std::vector<cl_uint>::const_iterator iter;

    QString s;

    int i = 0;

    for (iter = keys.begin(); iter != keys.end(); ++iter)
    {
        if ((i % 10) == 0)
        {
            s += "\n";

//            break;
        }

        // Extract the sort key part of the entry

        s += QString::number((KEY_MASK & (*iter)) >> INDEX_BITS) + " ";

        i++;
    }

    logger->logInfo(s);
}


void RadixSorter::logSums(Logger* logger)
{
    std::vector<cl_uint> sums = getSums();

    std::vector<cl_uint>::const_iterator iter;

    QString s;

    int i = 0;

    for (iter = sums.begin(); iter != sums.end(); ++iter)
    {
        if (i > 50)
        {
//            s += "...";

//            break;
        }

        s += QString::number(*iter) + " ";

        i++;
    }

    logger->logInfo(s);
}


void RadixSorter::logTotalFalses(Logger* logger)
{
    cl_uint totalFalses = getTotalFalses();

    QString s = QString::number(totalFalses);

    logger->logInfo(s);
}


void RadixSorter::logIsSorted(Logger* logger, cl_uint index)
{
    bool b = isSorted(index);

    QString s;

    if (b)
    {
        s = "Is sorted";
    }
    else
    {
        s = "Is NOT sorted";
    }


    logger->logInfo(s);
}


cl_uint RadixSorter::getKeyBits(cl_uint key)
{
    return KEY_MASK & key;
}


bool RadixSorter::isSorted(cl_uint index)
{
    std::vector<cl_uint> keys = getKeys(index);

    bool isSorted = true;

    for (uint i = 0; i < keys.size() - 1; i++)
    {
        if (keys[i] > keys[i + 1])
        {
            isSorted = false;

            break;
        }
    }

    return isSorted;
}


void RadixSorter::compute()
{
    // The sort key is stored in the upper 12 bits of the buffer values
    // so we start with the first bit of this sort key

    cl_uint bitMask = 1 << INDEX_BITS;

    // For each bit of the sort key

    for (cl_uint i = 0; i < 12; i++)
    {
        compute(bitMask);

        bitMask <<= 1;
    }
}


void RadixSorter::compute(cl_uint bitMask)
{

    //
    // Sum the elements
    //

    size_t requiredWorkItemsScan   = countRoundedUp / ELEMENTS_PER_WORK_ITEM_SCAN;
    size_t requiredWorkItemsOthers = countRoundedUp / ELEMENTS_PER_WORK_ITEM_OTHERS;

    size_t elementsPerGroupScan   = workGroupSize * ELEMENTS_PER_WORK_ITEM_SCAN;

    // If we have to write out group sums

    if (sumCount0 > 1)
    {
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 0, sizeof(cl_mem), &keyBuffers[inputBufferIndex] ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 1, sizeof(cl_uint), &count ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 2, sizeof(cl_uint) * elementsPerGroupScan, NULL ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 3, sizeof(cl_mem), &sumBuffer0 ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 4, sizeof(cl_uint), &DO_WRITE_SUMS ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 5, sizeof(cl_uint), &bitMask ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 6, sizeof(cl_mem), &lowerElementCountsBuffer ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 7, sizeof(cl_uint), &DO_NOT_WRITE_TOTAL_FALSES ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 8, sizeof(cl_mem), &dummyBuffer ) );

        CL_ERROR( clEnqueueNDRangeKernel(queue, kernelPrefixSumScan, 1, NULL, &requiredWorkItemsScan, &workGroupSize, 0, NULL, NULL) );

        size_t requiredWorkItemsScan2   = sumCount0RoundedUp / ELEMENTS_PER_WORK_ITEM_SCAN;

        // If we have to write out group sums a second time

        if (sumCount1 > 1)
        {
            //
            // Sum the groups
            //

            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 0, sizeof(cl_mem), &sumBuffer0 ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 1, sizeof(cl_uint), &sumCount0 ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 2, sizeof(cl_uint) * elementsPerGroupScan, NULL ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 3, sizeof(cl_mem), &sumBuffer1 ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 4, sizeof(cl_uint), &DO_WRITE_SUMS ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 5, sizeof(cl_uint), &NO_BITS ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 6, sizeof(cl_mem), &sumBuffer0 ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 7, sizeof(cl_uint), &DO_NOT_WRITE_TOTAL_FALSES ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 8, sizeof(cl_mem), &dummyBuffer ) );

            CL_ERROR( clEnqueueNDRangeKernel(queue, kernelPrefixSumScan, 1, NULL, &requiredWorkItemsScan2, &workGroupSize, 0, NULL, NULL) );


            //
            // Prefix sum the second groups on lowest level
            //

            size_t requiredWorkItemsScan3 = sumCount1RoundedUp / ELEMENTS_PER_WORK_ITEM_SCAN;

            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 0, sizeof(cl_mem), &sumBuffer1 ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 1, sizeof(cl_uint), &sumCount1 ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 2, sizeof(cl_uint) * elementsPerGroupScan, NULL ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 3, sizeof(cl_mem), &dummyBuffer ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 4, sizeof(cl_uint), &DO_NOT_WRITE_SUMS ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 5, sizeof(cl_uint), &NO_BITS ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 6, sizeof(cl_mem), &sumBuffer1 ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 7, sizeof(cl_uint), &DO_NOT_WRITE_TOTAL_FALSES ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 8, sizeof(cl_mem), &dummyBuffer ) );

            CL_ERROR( clEnqueueNDRangeKernel(queue, kernelPrefixSumScan, 1, NULL, &requiredWorkItemsScan3, &workGroupSize, 0, NULL, NULL) );

            //
            // Add the group1 prefixes to the group0 elements
            //

            size_t requiredWorkItemsOthers2 = sumCount0RoundedUp / ELEMENTS_PER_WORK_ITEM_OTHERS;

            CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 0, sizeof(cl_mem), &sumBuffer0 ) );
            CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 1, sizeof(cl_mem), &sumBuffer1 ) );
            CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 2, sizeof(cl_mem), &dummyBuffer ) );
            CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 3, sizeof(cl_uint), &dummyCount ) );
            CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 4, sizeof(cl_uint), &NO_BITS ) );
            CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 5, sizeof(cl_uint), &DO_NOT_WRITE_TOTAL_FALSES ) );
            CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 6, sizeof(cl_mem), &dummyBuffer ) );

            CL_ERROR( clEnqueueNDRangeKernel(queue, kernelAddGroupPrefix, 1, NULL, &requiredWorkItemsOthers2, &workGroupSize, 0, NULL, NULL) );
        }
        else
        {
            //
            // Prefix sum the first groups
            //

            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 0, sizeof(cl_mem), &sumBuffer0 ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 1, sizeof(cl_uint), &sumCount0 ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 2, sizeof(cl_uint) * elementsPerGroupScan, NULL ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 3, sizeof(cl_mem), &dummyBuffer ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 4, sizeof(cl_uint), &DO_NOT_WRITE_SUMS ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 5, sizeof(cl_uint), &NO_BITS ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 6, sizeof(cl_mem), &sumBuffer0 ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 7, sizeof(cl_uint), &DO_NOT_WRITE_TOTAL_FALSES ) );
            CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 8, sizeof(cl_mem), &dummyBuffer ) );

            CL_ERROR( clEnqueueNDRangeKernel(queue, kernelPrefixSumScan, 1, NULL, &requiredWorkItemsScan2, &workGroupSize, 0, NULL, NULL) );
        }

        //
        // Add the group0 prefixes to the elements
        //

        CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 0, sizeof(cl_mem), &lowerElementCountsBuffer ) );
        CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 1, sizeof(cl_mem), &sumBuffer0 ) );
        CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 2, sizeof(cl_mem), &keyBuffers[inputBufferIndex] ) );
        CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 3, sizeof(cl_uint), &count ) );
        CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 4, sizeof(cl_uint), &bitMask ) );
        CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 5, sizeof(cl_uint), &DO_WRITE_TOTAL_FALSES ) );
        CL_ERROR( clSetKernelArg(kernelAddGroupPrefix, 6, sizeof(cl_mem), &totalFalsesBuffer ) );

        CL_ERROR( clEnqueueNDRangeKernel(queue, kernelAddGroupPrefix, 1, NULL, &requiredWorkItemsOthers, &workGroupSize, 0, NULL, NULL) );
    }
    else
    {
        // Just compute everything in single work group

        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 0, sizeof(cl_mem), &keyBuffers[inputBufferIndex] ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 1, sizeof(cl_uint), &count ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 2, sizeof(cl_uint) * elementsPerGroupScan, NULL ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 3, sizeof(cl_mem), &dummyBuffer ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 4, sizeof(cl_uint), &DO_NOT_WRITE_SUMS ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 5, sizeof(cl_uint), &bitMask ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 6, sizeof(cl_mem), &lowerElementCountsBuffer ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 7, sizeof(cl_uint), &DO_WRITE_TOTAL_FALSES ) );
        CL_ERROR( clSetKernelArg(kernelPrefixSumScan, 8, sizeof(cl_mem), &totalFalsesBuffer ) );

        CL_ERROR( clEnqueueNDRangeKernel(queue, kernelPrefixSumScan, 1, NULL, &requiredWorkItemsScan, &workGroupSize, 0, NULL, NULL) );
    }

    //
    // Compute indices and scatter
    //

    CL_ERROR( clSetKernelArg(kernelComputeIndexAndScatter, 0, sizeof(cl_mem), &keyBuffers[inputBufferIndex] ) );
    CL_ERROR( clSetKernelArg(kernelComputeIndexAndScatter, 1, sizeof(cl_uint), &count ) );
    CL_ERROR( clSetKernelArg(kernelComputeIndexAndScatter, 2, sizeof(cl_mem), &lowerElementCountsBuffer ) );
    CL_ERROR( clSetKernelArg(kernelComputeIndexAndScatter, 3, sizeof(cl_mem), &totalFalsesBuffer ) );
    CL_ERROR( clSetKernelArg(kernelComputeIndexAndScatter, 4, sizeof(cl_uint), &bitMask ) );
    CL_ERROR( clSetKernelArg(kernelComputeIndexAndScatter, 5, sizeof(cl_mem), &keyBuffers[outputBufferIndex] ) );

    CL_ERROR( clEnqueueNDRangeKernel(queue, kernelComputeIndexAndScatter, 1, NULL, &requiredWorkItemsOthers, &workGroupSize, 0, NULL, NULL) );

    // Toggle buffers

    inputBufferIndex  = 1 - inputBufferIndex;
    outputBufferIndex = 1 - outputBufferIndex;
}
