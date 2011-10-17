#include "AverageVelocityCalculator.h"

#include "../computation/OpenCL.h"
#include "../graphics/OpenGL.h"

#include <CL/cl_gl.h>


const QString AverageVelocityCalculator::PROFILING_ELEMENT_NAME = "  AverageVelocity";


AverageVelocityCalculator::AverageVelocityCalculator(   const Logger*       logger,
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
                            0,
                            bufferSideLength,
                            bufferByteSize,
                            "src/kernels/averageVelocity.cl",
                            GL_RGBA32F)
{

    // Create kernels

    cl_int status;

    kernelAverageVelocity = clCreateKernel(program->getProgram(), "averageVelocity", &status);
    CL_ERROR(status);

    // Set kernel arguments

    CL_ERROR( clSetKernelArg(kernelAverageVelocity, 0, sizeof(bufferSideLength), &bufferSideLength) );

    kernelAverageVelocityProfilingId = profiler->registerElement(PROFILING_ELEMENT_NAME);
}


AverageVelocityCalculator::~AverageVelocityCalculator()
{
    profiler->deregisterElement(PROFILING_ELEMENT_NAME);
    clReleaseKernel(kernelAverageVelocity);
}


void AverageVelocityCalculator::compute(bool isProfiling, cl_mem densityDiscomfortVelocity)
{
    cl_int      status;

    cl_command_queue queue = context->queue;

    status = clEnqueueAcquireGLObjects(queue, 1, &densityDiscomfortVelocity, 0, NULL, NULL);
    CL_ERROR(status);

    CL_ERROR( clSetKernelArg(kernelAverageVelocity, 1, sizeof(cl_mem), &densityDiscomfortVelocity) );

    CL_PROFILE(kernelAverageVelocityProfilingId, isProfiling, queue,
            CL_ERROR( clEnqueueNDRangeKernel(queue, kernelAverageVelocity, 1, NULL, &threadCount, &workGroupSize, 0, NULL, &event) )
    );

    status = clEnqueueReleaseGLObjects(queue, 1, &densityDiscomfortVelocity, 0, NULL, NULL);
    CL_ERROR(status);
}
