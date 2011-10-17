#include "SharedBufferCalculator.h"

#include "../computation/OpenCL.h"
#include "../graphics/OpenGL.h"

#include <CL/cl_gl.h>


SharedBufferCalculator::SharedBufferCalculator( const Logger*       logger,
                                                Profiler*           profiler,
                                                const Context*      context,
                                                size_t              threadCount,
                                                size_t              workGroupSize,
                                                size_t              bufferCount,
                                                cl_uint             bufferSideLength,
                                                GLsizeiptr          bufferByteSize,
                                                QString             filename,
                                                GLenum              internalFormat)
: logger(logger),
  program(NULL),
  context(context),
  threadCount(threadCount),
  workGroupSize(workGroupSize),
  bufferSideLength(bufferSideLength),
  bufferCount(bufferCount),
  bufferByteSize(bufferByteSize),
  totalBufferSize(0),
  profiler(profiler),
  internalFormat(internalFormat)
{
    sharedTextureBuffers    = std::vector<cl_mem>(bufferCount, NULL);
    textureBuffers          = std::vector<GLuint>(bufferCount, 0);
    textureBufferTextures   = std::vector<BufferTexture*>(bufferCount, NULL);

    // Create program

    program = new Program(filename, context, "");


    initBuffersAndTextures();

}


SharedBufferCalculator::~SharedBufferCalculator()
{
    std::vector<cl_mem>::const_iterator iter0;

    for (iter0 = sharedTextureBuffers.begin(); iter0 != sharedTextureBuffers.end(); ++iter0)
    {
        clReleaseMemObject(*iter0);
    }

    std::vector<BufferTexture*>::const_iterator iter1;

    for (iter1 = textureBufferTextures.begin(); iter1 != textureBufferTextures.end(); ++iter1)
    {
        delete (*iter1);
    }

    glDeleteBuffers(bufferCount, &textureBuffers[0]);

    delete program;
}


void SharedBufferCalculator::initBuffersAndTextures()
{
    for (size_t i = 0; i < bufferCount; i++)
    {
        //
        // Create buffer object
        //

        glGenBuffers(1, &textureBuffers[i]);
        GL_ERROR;

        glBindBuffer(GL_TEXTURE_BUFFER, textureBuffers[i]);
        GL_ERROR;

        glBufferData(GL_TEXTURE_BUFFER, bufferByteSize, NULL, GL_DYNAMIC_COPY);
        GL_ERROR;
        totalBufferSize += bufferByteSize;

        cl_int status;

        sharedTextureBuffers[i] = clCreateFromGLBuffer(context->context, CL_MEM_READ_WRITE, textureBuffers[i], &status);
        CL_ERROR(status);

        //
        // Create texture
        //

        textureBufferTextures[i] = new BufferTexture();

        textureBufferTextures[i]->attachToBufferObject(textureBuffers[i], internalFormat);
    }
}


Vector4 SharedBufferCalculator::getValue(GLuint buffer, cl_uint positionX, cl_uint positionY, GLenum internalFormat, size_t bufferSideLength)
{
    glBindBuffer(GL_TEXTURE_BUFFER, buffer);
    GL_ERROR;

    int stride;

    switch (internalFormat)
    {
        case GL_R32F:
        {
            stride = 1;
            break;
        }

        case GL_RG32F:
        {
            stride = 2;
            break;
        }

        case GL_RGB32F:
        {
            stride = 3;
            break;
        }

        case GL_RGBA32F:
        {
            stride = 4;
            break;
        }

        default:
        {
            throw Exception("Invalid internal format in SharedBufferCalculator");
            break;
        }
    }

    GLintptr offset = (positionX + positionY * bufferSideLength) * stride * sizeof(GLfloat);
    GLsizeiptr length = stride * sizeof(GLfloat);

    GLfloat* mappedBuffer = (GLfloat*) glMapBufferRange( GL_TEXTURE_BUFFER, offset, length, GL_MAP_READ_BIT );
    GL_ERROR;

    Vector4 value;

    value.x = mappedBuffer[0];

    if (stride >= 2)
    {
        value.y = mappedBuffer[1];
    }

    if (stride >= 3)
    {
        value.z = mappedBuffer[2];
    }

    if (stride >= 4)
    {
        value.w = mappedBuffer[3];
    }

    glUnmapBuffer(GL_TEXTURE_BUFFER);
    GL_ERROR;

    glBindBuffer(GL_TEXTURE_BUFFER, 0);
    GL_ERROR;

    return value;
}


Vector4 SharedBufferCalculator::getValueIndexed(size_t bufferIndex, cl_uint positionX, cl_uint positionY)
{
    return SharedBufferCalculator::getValue(textureBuffers.at(bufferIndex), positionX, positionY, internalFormat, bufferSideLength);
}


const BufferTexture* SharedBufferCalculator::getBufferTexture(size_t i) const
{
    return textureBufferTextures.at(i);
}


cl_mem SharedBufferCalculator::getSharedBuffer(size_t i)
{
    return sharedTextureBuffers.at(i);
}


int SharedBufferCalculator::getTotalBufferSize()
{
    return totalBufferSize;
}
