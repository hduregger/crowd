#include "GradientCalculator.h"

#include "../computation/OpenCL.h"
#include "../graphics/OpenGL.h"
#include "../Exception.h"

#include <CL/cl_gl.h>


const QString GradientCalculator::PROFILING_ELEMENT_NAME = "  Gradient";


GradientCalculator::GradientCalculator( const Logger*       logger,
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
                            "src/kernels/gradient.cl",
                            GL_RGBA32F),
    kernelGradient(NULL),
    kernelGradientProfilingId(0)
{
    // Create kernels

    cl_int status;

    kernelGradient = clCreateKernel(program->getProgram(), "gradient", &status);
    CL_ERROR(status);

    // Set kernel arguments

    CL_ERROR( clSetKernelArg(kernelGradient, 0, sizeof(bufferSideLength), &bufferSideLength) );

    kernelGradientProfilingId = profiler->registerElement(PROFILING_ELEMENT_NAME);

    image01 = new Texture2DPair(bufferSideLength,
                                bufferSideLength,
                                GL_CLAMP_TO_EDGE,
                                GL_LINEAR,
                                GL_LINEAR,
                                GL_RGBA32F,
                                GL_RGBA,
                                GL_FLOAT,
                                NULL,
                                CL_MEM_READ_WRITE,
                                context);

    totalBufferSize += bufferSideLength * bufferSideLength * 4 * sizeof(GLfloat);

    image23 = new Texture2DPair(bufferSideLength,
                                bufferSideLength,
                                GL_CLAMP_TO_EDGE,
                                GL_LINEAR,
                                GL_LINEAR,
                                GL_RGBA32F,
                                GL_RGBA,
                                GL_FLOAT,
                                NULL,
                                CL_MEM_READ_WRITE,
                                context);

    totalBufferSize += bufferSideLength * bufferSideLength * 4 * sizeof(GLfloat);
}


GradientCalculator::~GradientCalculator()
{
    profiler->deregisterElement(PROFILING_ELEMENT_NAME);

    clReleaseKernel(kernelGradient);

    delete image01;
    delete image23;
}


void GradientCalculator::compute(bool isProfiling, cl_mem sharedPotentialBuffer)
{
    cl_command_queue queue = context->queue;

    //
    // Compute gradient
    //

    cl_mem clImage01 = image01->getImageShared();
    cl_mem clImage23 = image23->getImageShared();

    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &clImage01, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &clImage23, 0, NULL, NULL) );
    CL_ERROR( clEnqueueAcquireGLObjects(queue, 1, &sharedPotentialBuffer, 0, NULL, NULL) );

    CL_ERROR( clSetKernelArg(kernelGradient, 1, sizeof(cl_mem), &sharedPotentialBuffer ) );
    CL_ERROR( clSetKernelArg(kernelGradient, 2, sizeof(cl_mem), &clImage01 ) );
    CL_ERROR( clSetKernelArg(kernelGradient, 3, sizeof(cl_mem), &clImage23 ) );

    CL_PROFILE(kernelGradientProfilingId, isProfiling, queue,
            CL_ERROR( clEnqueueNDRangeKernel(queue, kernelGradient, 1, NULL, &threadCount, &workGroupSize, 0, NULL, &event) )
    );

    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &sharedPotentialBuffer, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &clImage01, 0, NULL, NULL) );
    CL_ERROR( clEnqueueReleaseGLObjects(queue, 1, &clImage23, 0, NULL, NULL) );
}


void GradientCalculator::getGradient(cl_uint positionX, cl_uint positionY, AgentGroupRenderState::State state, cl_float* gradientX, cl_float* gradientY)
{
    std::vector<float> gradient01;
    std::vector<float> gradient23;

    gradient01.resize(bufferSideLength * bufferSideLength * 4 * sizeof(GLfloat));
    gradient23.resize(bufferSideLength * bufferSideLength * 4 * sizeof(GLfloat));

    glActiveTexture(GL_TEXTURE0);
    image01->getTexture2D()->enable();
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, &gradient01[0]);

    glActiveTexture(GL_TEXTURE1);
    image23->getTexture2D()->enable();
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, &gradient23[0]);

    int texel = positionX + positionY * bufferSideLength;
    int texelIndex = texel * 4;


    switch (state)
    {
        case AgentGroupRenderState::GROUP0:
        {
            *gradientX = gradient01[texelIndex    ];
            *gradientY = gradient01[texelIndex + 1];

            break;
        }

        case AgentGroupRenderState::GROUP1:
        {
            *gradientX = gradient01[texelIndex + 2];
            *gradientY = gradient01[texelIndex + 3];

            break;
        }

        case AgentGroupRenderState::GROUP2:
        {
            *gradientX = gradient23[texelIndex    ];
            *gradientY = gradient23[texelIndex + 1];

            break;
        }

        case AgentGroupRenderState::GROUP3:
        {
            *gradientX = gradient23[texelIndex + 2];
            *gradientY = gradient23[texelIndex + 3];

            break;
        }

        default:
        {
            throw Exception("Invalid agent group for picking");
            break;
        }
    }

    glActiveTexture(GL_TEXTURE0);
    image01->getTexture2D()->disable();

    glActiveTexture(GL_TEXTURE1);
    image23->getTexture2D()->disable();
}


cl_mem GradientCalculator::getGradients01Shared()
{
    return image01->getImageShared();
}


cl_mem GradientCalculator::getGradients23Shared()
{
    return image23->getImageShared();
}


const Texture2D* GradientCalculator::getGradients01() const
{
    return image01->getTexture2D();
}


const Texture2D* GradientCalculator::getGradients23() const
{
    return image23->getTexture2D();
}
