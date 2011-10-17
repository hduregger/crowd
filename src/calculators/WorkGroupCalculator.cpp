#include "WorkGroupCalculator.h"

#include "../computation/OpenCL.h"
#include "../graphics/OpenGL.h"

#include <CL/cl_gl.h>


WorkGroupCalculator::WorkGroupCalculator(   const Logger*   logger,
                                            Profiler*       profiler,
                                            const Context*  context,
                                            size_t          threadCount,
                                            size_t          workGroupSize,
                                            cl_uint         bufferSideLength,
                                            GLsizeiptr      bufferByteSize,
                                            cl_uint         workGroupSideLength)
: SharedBufferCalculator(logger,
                         profiler,
                         context,
                         threadCount,
                         workGroupSize,
                         1,
                         bufferSideLength,
                         bufferByteSize,
                         "src/kernels/workGroups.cl",
                         GL_R32F),
  kernelWorkGroups(NULL)
{
    // Create kernels

    cl_int status;

    kernelWorkGroups = clCreateKernel(program->getProgram(), "workGroups", &status);
    CL_ERROR(status);

    // Set kernel arguments

    CL_ERROR( clSetKernelArg(kernelWorkGroups, 0, sizeof(bufferSideLength), &bufferSideLength) );
    CL_ERROR( clSetKernelArg(kernelWorkGroups, 1, sizeof(workGroupSideLength), &workGroupSideLength) );
}


WorkGroupCalculator::~WorkGroupCalculator()
{
}


void WorkGroupCalculator::compute()
{
    cl_int      status;

    cl_command_queue queue = context->queue;

    //
    // Compute gradient
    //

    status = clEnqueueAcquireGLObjects(queue, 1, &sharedTextureBuffers[0], 0, NULL, NULL);
    CL_ERROR(status);


    CL_ERROR( clSetKernelArg(kernelWorkGroups, 2, sizeof(cl_mem), &sharedTextureBuffers[0] ) );

    CL_ERROR( clEnqueueNDRangeKernel(queue, kernelWorkGroups, 1, NULL, &threadCount, &workGroupSize, 0, NULL, NULL) );

    status = clEnqueueReleaseGLObjects(queue, 1, &sharedTextureBuffers[0], 0, NULL, NULL);
    CL_ERROR(status);

    clReleaseKernel(kernelWorkGroups);
    kernelWorkGroups = NULL;
}


const BufferTexture* WorkGroupCalculator::getWorkGroups() const
{
    return getBufferTexture(0);
}
