#include "WorkItemCalculator.h"

#include "../computation/OpenCL.h"
#include "../graphics/OpenGL.h"

#include <CL/cl_gl.h>


WorkItemCalculator::WorkItemCalculator( const Logger*   logger,
                                        Profiler*       profiler,
                                        const Context*  context,
                                        size_t          threadCount,
                                        size_t          workGroupSize,
                                        cl_uint         bufferSideLength,
                                        GLsizeiptr      bufferByteSize,
                                        cl_uint         workGroupSideLength)
: SharedBufferCalculator(   logger,
                            profiler,
                            context,
                            threadCount,
                            workGroupSize,
                            1,
                            bufferSideLength,
                            bufferByteSize,
                            "src/kernels/workItems.cl",
                            GL_R32F),
  kernelWorkItems(NULL)
{
    // Create kernels

    cl_int status;

    kernelWorkItems = clCreateKernel(program->getProgram(), "workItems", &status);
    CL_ERROR(status);

    // Set kernel arguments

    CL_ERROR( clSetKernelArg(kernelWorkItems, 0, sizeof(bufferSideLength), &bufferSideLength) );
    CL_ERROR( clSetKernelArg(kernelWorkItems, 1, sizeof(workGroupSideLength), &workGroupSideLength) );
}


WorkItemCalculator::~WorkItemCalculator()
{
}


void WorkItemCalculator::compute()
{
    cl_int      status;

    //
    // Compute gradient
    //

    cl_command_queue queue = context->queue;

    status = clEnqueueAcquireGLObjects(queue, 1, &sharedTextureBuffers[0], 0, NULL, NULL);
    CL_ERROR(status);


    CL_ERROR( clSetKernelArg(kernelWorkItems, 2, sizeof(cl_mem), &sharedTextureBuffers[0] ) );

    CL_ERROR( clEnqueueNDRangeKernel(queue, kernelWorkItems, 1, NULL, &threadCount, &workGroupSize, 0, NULL, NULL) );

    status = clEnqueueReleaseGLObjects(queue, 1, &sharedTextureBuffers[0], 0, NULL, NULL);
    CL_ERROR(status);

    clReleaseKernel(kernelWorkItems);
    kernelWorkItems = NULL;
}


const BufferTexture* WorkItemCalculator::getWorkItems() const
{
    return getBufferTexture(0);
}
