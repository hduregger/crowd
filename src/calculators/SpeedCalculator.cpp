#include "SpeedCalculator.h"

#include "../computation/OpenCL.h"
#include "../graphics/OpenGL.h"

#include <CL/cl_gl.h>

const QString SpeedCalculator::PROFILING_ELEMENT_NAME = "  Speed";


SpeedCalculator::SpeedCalculator(   const Logger*       logger,
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
                            "src/kernels/speed.cl",
                            GL_RGBA32F),
    minimumDensity(0.5f),
    maximumDensity(0.6f),
    maximumSpeed(12.0f)
{
    // Create kernels

    cl_int status;

    speed = clCreateKernel(program->getProgram(), "speed", &status);
    CL_ERROR(status);


    speedProfilingId = profiler->registerElement(PROFILING_ELEMENT_NAME);

    // Set kernel arguments

    CL_ERROR( clSetKernelArg(speed, 0, sizeof(bufferSideLength), &bufferSideLength) );
    CL_ERROR( clSetKernelArg(speed, 3, sizeof(cl_float), &minimumDensity) );
    CL_ERROR( clSetKernelArg(speed, 4, sizeof(cl_float), &maximumDensity) );
    CL_ERROR( clSetKernelArg(speed, 5, sizeof(cl_float), &maximumSpeed) );
}


SpeedCalculator::~SpeedCalculator()
{
    profiler->deregisterElement(PROFILING_ELEMENT_NAME);
}


void SpeedCalculator::compute(bool isProfiling, cl_mem sharedDensityDiscomfortVelocity)
{
    cl_int      status;

    cl_command_queue queue = context->queue;

    status = clEnqueueAcquireGLObjects(queue, 1, &sharedDensityDiscomfortVelocity, 0, NULL, NULL);
    CL_ERROR(status);
    status = clEnqueueAcquireGLObjects(queue, 1, &sharedTextureBuffers[0], 0, NULL, NULL);
    CL_ERROR(status);

    CL_ERROR( clSetKernelArg(speed, 1, sizeof(cl_mem), &sharedDensityDiscomfortVelocity) );
    CL_ERROR( clSetKernelArg(speed, 2, sizeof(cl_mem), &sharedTextureBuffers[0]) );

    CL_PROFILE(speedProfilingId, isProfiling, queue,
            CL_ERROR( clEnqueueNDRangeKernel(queue, speed, 1, NULL, &threadCount, &workGroupSize, 0, NULL, &event) )
    );

    status = clEnqueueReleaseGLObjects(queue, 1, &sharedTextureBuffers[0], 0, NULL, NULL);
    CL_ERROR(status);
    status = clEnqueueReleaseGLObjects(queue, 1, &sharedDensityDiscomfortVelocity, 0, NULL, NULL);
    CL_ERROR(status);

}


float SpeedCalculator::getMinimumDensity()
{
    return minimumDensity;
}


float SpeedCalculator::getMaximumDensity()
{
    return maximumDensity;
}


void SpeedCalculator::setMinimumDensity(float density)
{
    minimumDensity = density;
    CL_ERROR( clSetKernelArg(speed, 3, sizeof(cl_float), &minimumDensity) );
}


void SpeedCalculator::setMaximumDensity(float density)
{
    maximumDensity = density;
    CL_ERROR( clSetKernelArg(speed, 4, sizeof(cl_float), &maximumDensity) );
}


void SpeedCalculator::setMaximumSpeed(float speed)
{
    maximumSpeed = speed;
    CL_ERROR( clSetKernelArg(this->speed, 5, sizeof(cl_float), &maximumSpeed) );
}


float SpeedCalculator::getMaximumSpeed() const
{
    return maximumSpeed;
}


Vector4 SpeedCalculator::getSpeed(cl_uint positionX, cl_uint positionY)
{
    return getValueIndexed(0, positionX, positionY);
}


cl_mem SpeedCalculator::getSpeedsShared()
{
    return getSharedBuffer(0);
}


const BufferTexture* SpeedCalculator::getSpeeds() const
{
    return getBufferTexture(0);
}
