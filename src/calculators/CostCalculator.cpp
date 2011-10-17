#include "CostCalculator.h"

#include "../computation/OpenCL.h"
#include "../graphics/OpenGL.h"

#include <CL/cl_gl.h>


const QString CostCalculator::PROFILING_ELEMENT_NAME = "  Cost";

CostCalculator::CostCalculator( const Logger*       logger,
                                Profiler*           profiler,
                                const Context*      context,
                                size_t              threadCount,
                                size_t              workGroupSize,
                                cl_uint             bufferSideLength,
                                GLsizeiptr          bufferByteSize)
:   SharedBufferCalculator( logger,
                            profiler,
                            context,
                            threadCount,
                            workGroupSize,
                            1,
                            bufferSideLength,
                            bufferByteSize,
                            "src/kernels/cost.cl",
                            GL_RGBA32F),
    costWeightPathLength(1.0f),
    costWeightTime(1.0f),
    costWeightDiscomfort(1.0f)
{
    // Create kernels

    cl_int status;

    kernelCost = clCreateKernel(program->getProgram(), "cost", &status);
    CL_ERROR(status);

    kernelCostProfilingId = profiler->registerElement(PROFILING_ELEMENT_NAME);

    // Set kernel arguments

    CL_ERROR( clSetKernelArg(kernelCost, 3, sizeof(cl_float), &costWeightPathLength) );
    CL_ERROR( clSetKernelArg(kernelCost, 4, sizeof(cl_float), &costWeightTime) );
    CL_ERROR( clSetKernelArg(kernelCost, 5, sizeof(cl_float), &costWeightDiscomfort) );
    CL_ERROR( clSetKernelArg(kernelCost, 6, sizeof(cl_int),   &bufferSideLength) );
}


CostCalculator::~CostCalculator()
{
    profiler->deregisterElement(PROFILING_ELEMENT_NAME);
    clReleaseKernel(kernelCost);
}


void CostCalculator::compute(bool isProfiling, cl_mem sharedSpeed, cl_mem sharedDensitiesDiscomfortsVelocities)
{
    cl_int      status;

    cl_command_queue queue = context->queue;

    //
    // Compute gradient
    //

    status = clEnqueueAcquireGLObjects(queue, 1, &sharedTextureBuffers[0], 0, NULL, NULL);
    CL_ERROR(status);
    status = clEnqueueAcquireGLObjects(queue, 1, &sharedSpeed, 0, NULL, NULL);
    CL_ERROR(status);
    status = clEnqueueAcquireGLObjects(queue, 1, &sharedDensitiesDiscomfortsVelocities, 0, NULL, NULL);
    CL_ERROR(status);

    CL_ERROR( clSetKernelArg(kernelCost, 0, sizeof(cl_mem), &sharedDensitiesDiscomfortsVelocities ) );
    CL_ERROR( clSetKernelArg(kernelCost, 1, sizeof(cl_mem), &sharedSpeed) );
    CL_ERROR( clSetKernelArg(kernelCost, 2, sizeof(cl_mem), &sharedTextureBuffers[0]) );

    CL_PROFILE(kernelCostProfilingId, isProfiling, queue,
            CL_ERROR( clEnqueueNDRangeKernel(queue, kernelCost, 1, NULL, &threadCount, &workGroupSize, 0, NULL, &event) )
    );

    status = clEnqueueReleaseGLObjects(queue, 1, &sharedDensitiesDiscomfortsVelocities, 0, NULL, NULL);
    CL_ERROR(status);
    status = clEnqueueReleaseGLObjects(queue, 1, &sharedSpeed, 0, NULL, NULL);
    CL_ERROR(status);
    status = clEnqueueReleaseGLObjects(queue, 1, &sharedTextureBuffers[0], 0, NULL, NULL);
    CL_ERROR(status);
}


cl_mem CostCalculator::getCostsShared()
{
    return getSharedBuffer(0);
}


Vector4 CostCalculator::getCost(cl_uint positionX, cl_uint positionY)
{
    return getValueIndexed(0, positionX, positionY);
}


void CostCalculator::setCostWeightPathLength(float pathLength)
{
    costWeightPathLength = pathLength;
    CL_ERROR( clSetKernelArg(kernelCost, 3, sizeof(cl_float), &costWeightPathLength) );
}


void CostCalculator::setCostWeightTime(float time)
{
    costWeightTime = time;
    CL_ERROR( clSetKernelArg(kernelCost, 4, sizeof(cl_float), &costWeightTime) );
}


void CostCalculator::setCostWeightDiscomfort(float discomfort)
{
    costWeightDiscomfort = discomfort;
    CL_ERROR( clSetKernelArg(kernelCost, 5, sizeof(cl_float), &costWeightDiscomfort) );
}


const BufferTexture* CostCalculator::getCosts() const
{
    return getBufferTexture(0);
}
