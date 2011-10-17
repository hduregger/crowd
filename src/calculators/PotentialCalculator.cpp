#include "PotentialCalculator.h"

#include "../computation/OpenCL.h"
#include "../graphics/OpenGL.h"
#include "../Number.h"
#include "../SystemTime.h"

#include <CL/cl_gl.h>

const cl_int   PotentialCalculator::UPDATE_METHOD_UPDATE_ALL         = 0;
const cl_int   PotentialCalculator::UPDATE_METHOD_UPDATE_SELECTIVELY = 1;
const QString  PotentialCalculator::PROFILING_ELEMENT_NAME           = "  PotentialSolver";


PotentialCalculator::PotentialCalculator(   const Logger*       logger,
                                            Profiler*           profiler,
                                            const Context*      context,
                                            size_t              threadCount,
                                            size_t              workGroupSize,
                                            cl_uint             bufferSideLength,
                                            GLsizeiptr          bufferByteSize,
                                            cl_mem              basePotential,
                                            cl_uint             workGroupSideLength)
:   SharedBufferCalculator( logger,
                            profiler,
                            context,
                            threadCount,
                            workGroupSize,
                            1,
                            bufferSideLength,
                            bufferByteSize,
                            "src/kernels/potential.cl",
                            GL_RGBA32F),
    kernelInit(NULL),
    kernelSolveLarge(NULL),
    baseGroupStates(NULL),
    nullBuffer(NULL),
    groupStatesReadIndex(0),
    groupStatesWriteIndex(1),
    outerLoopCount(0),
    wasConverged(true),
    iCurrent(0),
    isBreakingAfterOuterStep(false),
    isOnlyInitializingFirst(false), // NOTE: only use for debug, else gradient will contain random data after first step
    isFirstStep(true),
    kernelSolveLargeProfilingId(0),
    innerLoopCount(10),
    workGroupSideLength(workGroupSideLength),
    updateState(UpdateState::ALL),
    basePotential(basePotential)
{
    // Create kernels

    cl_int status;

    kernelInit = clCreateKernel(program->getProgram(), "initialize", &status);
    CL_ERROR(status);

    kernelSolveLarge = clCreateKernel(program->getProgram(), "potential", &status);
    CL_ERROR(status);

    //
    // Create group states buffers
    //

    baseGroupStates = new TextureBufferTripple(sizeof(cl_int) * threadCount, NULL, GL_DYNAMIC_COPY, GL_R32I, CL_MEM_READ_WRITE, context);
    totalBufferSize += sizeof(cl_int) * threadCount;

    groupStates.resize(2);
    groupStates[groupStatesReadIndex]  = new TextureBufferTripple(sizeof(cl_int) * threadCount, NULL, GL_DYNAMIC_COPY, GL_R32I, CL_MEM_READ_WRITE, context);
    groupStates[groupStatesWriteIndex] = new TextureBufferTripple(sizeof(cl_int) * threadCount, NULL, GL_DYNAMIC_COPY, GL_R32I, CL_MEM_READ_WRITE, context);
    totalBufferSize += sizeof(cl_int) * threadCount;
    totalBufferSize += sizeof(cl_int) * threadCount;

    //
    // Set kernel arguments
    //

    CL_ERROR( clSetKernelArg(kernelSolveLarge, 0, sizeof(bufferSideLength), &bufferSideLength) );
    CL_ERROR( clSetKernelArg(kernelSolveLarge, 1, sizeof(workGroupSideLength), &workGroupSideLength) );

    CL_ERROR( clSetKernelArg(kernelSolveLarge, 4, sizeof(cl_float4) * (workGroupSideLength + 2) * (workGroupSideLength + 2), NULL) );
    CL_ERROR( clSetKernelArg(kernelSolveLarge, 5, sizeof(cl_uint), &innerLoopCount) );
    CL_ERROR( clSetKernelArg(kernelSolveLarge, 6, sizeof(cl_int) * workGroupSize, NULL) );


    kernelSolveLargeProfilingId = profiler->registerElement(PROFILING_ELEMENT_NAME);

    //
    // Initialize base group states to update all tiles.
    // Later we just copy the buffer over to initialize the solver.
    //

    const size_t globalWorkSize[2] = { bufferSideLength,    bufferSideLength    };
    const size_t localWorkSize[2]  = { workGroupSideLength, workGroupSideLength };

    cl_command_queue queue = context->queue;

    cl_mem baseGroupStatesBuffer = baseGroupStates->getBufferShared();

    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &baseGroupStatesBuffer, 0, NULL, NULL) );

    CL_ERROR( clSetKernelArg(kernelInit, 0, sizeof(bufferSideLength), &bufferSideLength) );
    CL_ERROR( clSetKernelArg(kernelInit, 1, sizeof(cl_mem), &basePotential) );
    CL_ERROR( clSetKernelArg(kernelInit, 2, sizeof(cl_mem), &baseGroupStatesBuffer) );
    CL_ERROR( clSetKernelArg(kernelInit, 3, sizeof(cl_int) * workGroupSize, NULL) );

    CL_ERROR( clEnqueueNDRangeKernel(queue, kernelInit, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL) );

    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &baseGroupStatesBuffer, 0, NULL, NULL) );

    clReleaseKernel(kernelInit);
    kernelInit = NULL;

    // Create null buffer because we can't pass NULL pointer to kernel currently (not clear in the specification)

    nullBuffer = clCreateBuffer(context->context, CL_MEM_READ_WRITE, 1, NULL, &status);
    CL_ERROR(status);
    totalBufferSize += 1;
}


PotentialCalculator::~PotentialCalculator()
{
    profiler->deregisterElement(PROFILING_ELEMENT_NAME);

    delete baseGroupStates;
    delete groupStates[0];
    delete groupStates[1];

    clReleaseMemObject(nullBuffer);

    clReleaseKernel(kernelSolveLarge);
}


void PotentialCalculator::setInnerLoopCount(cl_uint count)
{
    innerLoopCount = count;
    CL_ERROR( clSetKernelArg(kernelSolveLarge, 5, sizeof(cl_uint), &innerLoopCount ) );
}


bool PotentialCalculator::compute(bool isProfiling, cl_mem sharedTextureBufferCost)
{
    bool isRequiringGroupStates = updateState == UpdateState::SELECTIVELY;

    // Acquire base potential and working potential buffers

    cl_mem groupStatesReadBuffer;
    cl_mem groupStatesWriteBuffer;

    cl_command_queue queue = context->queue;

    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &sharedTextureBuffers[0], 0, NULL, NULL) );

    CL_ERROR( clSetKernelArg(kernelSolveLarge, 3, sizeof(cl_mem), &sharedTextureBuffers[0]) );

    if (isRequiringGroupStates)
    {
        groupStatesReadBuffer  = groupStates[groupStatesReadIndex]->getBufferShared();
        groupStatesWriteBuffer = groupStates[groupStatesWriteIndex]->getBufferShared();

        CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &groupStatesReadBuffer, 0, NULL, NULL) );
        CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &groupStatesWriteBuffer, 0, NULL, NULL) );
    }
    else
    {
        groupStatesReadBuffer  = nullBuffer;
        groupStatesWriteBuffer = nullBuffer;
    }

    //
    // If the computation converged previously we start over by initializing the buffers
    //

    if (wasConverged)
    {
        if (isRequiringGroupStates)
        {
            cl_mem baseGroupStatesBuffer = baseGroupStates->getBufferShared();

            CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &baseGroupStatesBuffer, 0, NULL, NULL) );

            CL_ERROR( clEnqueueCopyBuffer(queue, baseGroupStatesBuffer, groupStatesReadBuffer, 0, 0, sizeof(cl_int) * threadCount, 0, NULL, NULL) );
//            CL_ERROR( clEnqueueCopyBuffer(queue, baseGroupStatesBuffer, groupStatesWriteBuffer, 0, 0, sizeof(cl_int) * threadCount, 0, NULL, NULL) );

            CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &baseGroupStatesBuffer, 0, NULL, NULL) );
        }


        // Copy base potential buffer into computation buffer and base group states into states

        CL_ERROR( clEnqueueCopyBuffer(queue, basePotential, sharedTextureBuffers[0], 0, 0, bufferByteSize, 0, NULL, NULL) );
    }

    //
    // Solve
    //

    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &sharedTextureBufferCost, 0, NULL, NULL) );

    CL_ERROR( clSetKernelArg(kernelSolveLarge, 2, sizeof(cl_mem), &sharedTextureBufferCost ) );

    bool isConverged = false;


    // If we don't just initialize this step

    if (!isOnlyInitializingFirst || (isOnlyInitializingFirst && !isFirstStep))
    {
        while (true)
        {
//            logger->logInfo(QString::number(iCurrent));

            if (isRequiringGroupStates)
            {
                groupStatesReadBuffer  = groupStates[groupStatesReadIndex]->getBufferShared();
                groupStatesWriteBuffer = groupStates[groupStatesWriteIndex]->getBufferShared();
            }

            cl_int updateMethod = static_cast<cl_int> (updateState);

            CL_ERROR( clSetKernelArg(kernelSolveLarge, 7, sizeof(cl_mem), &groupStatesReadBuffer ) );
            CL_ERROR( clSetKernelArg(kernelSolveLarge, 8, sizeof(cl_mem), &groupStatesWriteBuffer ) );
            CL_ERROR( clSetKernelArg(kernelSolveLarge, 9, sizeof(cl_int), &updateMethod ) );

            const size_t globalWorkSize[2] = { bufferSideLength,    bufferSideLength    };
            const size_t localWorkSize[2]  = { workGroupSideLength, workGroupSideLength };

            // Solve large
            CL_PROFILE(kernelSolveLargeProfilingId, isProfiling, queue,
                  CL_ERROR( clEnqueueNDRangeKernel(queue, kernelSolveLarge, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, &event) )
            );

            // Swap group state buffers

            if (isRequiringGroupStates)
            {
                groupStatesReadIndex  = 1 - groupStatesReadIndex;
                groupStatesWriteIndex = 1 - groupStatesWriteIndex;
            }

            iCurrent++;

            if (iCurrent >= outerLoopCount)
            {
                isConverged = true;
                break;
            }

            if (isBreakingAfterOuterStep)
            {
                break;
            }
        }

    }

    if (isConverged)
    {
        iCurrent = 0;
    }

    if (isRequiringGroupStates)
    {
        CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &groupStatesWriteBuffer, 0, NULL, NULL) );
        CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &groupStatesReadBuffer, 0, NULL, NULL) );
    }

    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &sharedTextureBufferCost, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &sharedTextureBuffers[0], 0, NULL, NULL) );

    wasConverged = isConverged;

    isFirstStep = isConverged;

    return isConverged;
}


int PotentialCalculator::getGroupStatesReadIndex() const
{
    return groupStatesReadIndex;
}


void PotentialCalculator::setOuterLoopCount(int outerLoopCount)
{
    this->outerLoopCount = outerLoopCount;
}


size_t PotentialCalculator::getOuterLoopCount()
{
    return outerLoopCount;
}


void PotentialCalculator::setIsBreakingAfterOuterStep(bool isBreaking)
{
    isBreakingAfterOuterStep = isBreaking;
}


Vector4 PotentialCalculator::getPotential(cl_uint positionX, cl_uint positionY)
{
    return getValueIndexed(0, positionX, positionY);
}


cl_mem PotentialCalculator::getPotentialsShared()
{
    return getSharedBuffer(0);
}


const BufferTexture* PotentialCalculator::getPotentials() const
{
    return getBufferTexture(0);
}


const BufferTexture* PotentialCalculator::getGroupStates(int index) const
{
    return groupStates[index]->getBufferTexture();
}


void PotentialCalculator::setUpdateState(UpdateState::State state)
{
    updateState = state;
}
