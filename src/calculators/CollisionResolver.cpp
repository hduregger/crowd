#include "CollisionResolver.h"

#include "../computation/OpenCL.h"

#include <CL/cl_gl.h>


const uint      CollisionResolver::BUCKET_ENTRIES  = 4;
const QString   CollisionResolver::PROFILING_ELEMENT_NAME0 = "  SortAgentsIntoBuckets";
const QString   CollisionResolver::PROFILING_ELEMENT_NAME1 = "  ResolveCollisions";


CollisionResolver::CollisionResolver(   const Context*      context,
                                        Profiler*           profiler,
                                        size_t              workGroupSize,
                                        size_t              count,
                                        cl_uint             bufferSideLength)
:   program(NULL),
    context(context),
    zeroAgentCounts(NULL),
    sortAgentsIntoBuckets(NULL),
    resolveCollisions(NULL),
    workGroupSize(workGroupSize),
    count(count),
    buckets(NULL),
    agentCounts(NULL),
    bufferSideLength(bufferSideLength),
    bucketCount(bufferSideLength * bufferSideLength),
    totalBufferSize(0),
    profiler(profiler)
{
    // Create program

    program = new Program("src/kernels/resolveCollisions.cl", context, "-DBUCKET_ENTRIES_DEFINITION=" + QString::number(BUCKET_ENTRIES));

    // Create kernels

    cl_int status;

    zeroAgentCounts = clCreateKernel(program->getProgram(), "zeroAgentCounts", &status);
    CL_ERROR(status);

    sortAgentsIntoBuckets = clCreateKernel(program->getProgram(), "sortAgentsIntoBuckets", &status);
    CL_ERROR(status);

    resolveCollisions = clCreateKernel(program->getProgram(), "resolveCollisions", &status);
    CL_ERROR(status);


    // There are several bucket entries for each bucket in the buffer.

    buckets = clCreateBuffer(context->context, CL_MEM_READ_WRITE, sizeof(cl_uint) * BUCKET_ENTRIES * bucketCount, NULL, &status);
    CL_ERROR(status);
    totalBufferSize += sizeof(cl_uint) * BUCKET_ENTRIES * bucketCount;

    // In this buffer we store the agent count inside each cell

    agentCounts = clCreateBuffer(context->context, CL_MEM_READ_WRITE, sizeof(cl_uint) * bucketCount, NULL, &status);
    CL_ERROR(status);
    totalBufferSize += sizeof(cl_uint) * bucketCount;


    kernelSortAgentsIntoBucketsProfilingId = profiler->registerElement(PROFILING_ELEMENT_NAME0);
    kernelResolveCollisionsProfilingId     = profiler->registerElement(PROFILING_ELEMENT_NAME1);
}


CollisionResolver::~CollisionResolver()
{
    profiler->deregisterElement(PROFILING_ELEMENT_NAME0);
    profiler->deregisterElement(PROFILING_ELEMENT_NAME1);

    delete program;

    clReleaseMemObject(buckets);
    clReleaseMemObject(agentCounts);

    clReleaseKernel(zeroAgentCounts);
    clReleaseKernel(sortAgentsIntoBuckets);
    clReleaseKernel(resolveCollisions);
}


void CollisionResolver::compute(bool        isProfiling,
                                cl_mem      positions,
                                cl_mem      radii,
                                cl_mem      ids,
                                cl_float    maximumRadius,
                                cl_mem      sharedPotentials)
{
    CL_ERROR( clSetKernelArg(zeroAgentCounts, 0, sizeof(cl_mem), &agentCounts) );

    cl_command_queue queue = context->queue;

    CL_ERROR( clEnqueueNDRangeKernel(queue, zeroAgentCounts, 1, NULL, &bucketCount, &workGroupSize, 0, NULL, NULL) );


    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &positions, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &radii, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &ids, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &sharedPotentials, 0, NULL, NULL) );

    CL_ERROR( clSetKernelArg(sortAgentsIntoBuckets, 0, sizeof(cl_mem),   &positions) );
    CL_ERROR( clSetKernelArg(sortAgentsIntoBuckets, 1, sizeof(cl_uint),  &bufferSideLength) );
    CL_ERROR( clSetKernelArg(sortAgentsIntoBuckets, 2, sizeof(cl_mem),   &buckets) );
    CL_ERROR( clSetKernelArg(sortAgentsIntoBuckets, 3, sizeof(cl_mem),   &agentCounts) );

    CL_PROFILE(kernelSortAgentsIntoBucketsProfilingId, isProfiling, queue,
            CL_ERROR( clEnqueueNDRangeKernel(queue, sortAgentsIntoBuckets, 1, NULL, &count, &workGroupSize, 0, NULL, &event) )
    );


    CL_ERROR( clSetKernelArg(resolveCollisions, 0, sizeof(cl_mem),   &positions) );
    CL_ERROR( clSetKernelArg(resolveCollisions, 1, sizeof(cl_mem),   &radii) );
    CL_ERROR( clSetKernelArg(resolveCollisions, 2, sizeof(cl_mem),   &ids) );
    CL_ERROR( clSetKernelArg(resolveCollisions, 3, sizeof(cl_uint),  &count) );
    CL_ERROR( clSetKernelArg(resolveCollisions, 4, sizeof(cl_mem),   &buckets) );
    CL_ERROR( clSetKernelArg(resolveCollisions, 5, sizeof(cl_mem),   &agentCounts) );
    CL_ERROR( clSetKernelArg(resolveCollisions, 6, sizeof(cl_uint),  &bufferSideLength) );
    CL_ERROR( clSetKernelArg(resolveCollisions, 7, sizeof(cl_float), &maximumRadius) );
    CL_ERROR( clSetKernelArg(resolveCollisions, 8, sizeof(cl_mem),   &sharedPotentials) );

    CL_PROFILE(kernelResolveCollisionsProfilingId, isProfiling, queue,
            CL_ERROR( clEnqueueNDRangeKernel(queue, resolveCollisions, 1, NULL, &count, &workGroupSize, 0, NULL, &event) )
    );

    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &sharedPotentials, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &ids, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &radii, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &positions, 0, NULL, NULL) );
}


int CollisionResolver::getTotalBufferSize()
{
    return totalBufferSize;
}
