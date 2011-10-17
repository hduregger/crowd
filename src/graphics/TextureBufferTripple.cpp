#include "TextureBufferTripple.h"

#include "OpenGL.h"
#include "../computation/OpenCL.h"


TextureBufferTripple::TextureBufferTripple( GLsizeiptr     size,
                                            const void*    data,
                                            GLenum         usage,
                                            GLenum         internalFormat,
                                            cl_mem_flags   flags,
                                            const Context* context)
:   buffer(0),
    bufferShared(NULL),
    bufferTexture(NULL)
{
    glGenBuffers(1, &buffer);
    GL_ERROR;

    //
    // Create buffer object
    //

    glBindBuffer(GL_TEXTURE_BUFFER, buffer);
    GL_ERROR;

    glBufferData(GL_TEXTURE_BUFFER, size, data, usage);
    GL_ERROR;

    //
    // Create shared buffer
    //

    cl_int status;

    bufferShared = clCreateFromGLBuffer(context->context, flags, buffer, &status);
    CL_ERROR(status);

    //
    // Create buffer texture
    //

    bufferTexture = new BufferTexture();
    bufferTexture->attachToBufferObject(buffer, internalFormat);
}


TextureBufferTripple::~TextureBufferTripple()
{
    delete bufferTexture;
    glDeleteBuffers(1, &buffer);
    clReleaseMemObject(bufferShared);
}


GLuint TextureBufferTripple::getBuffer() const
{
    return buffer;
}


cl_mem TextureBufferTripple::getBufferShared() const
{
    return bufferShared;
}


const BufferTexture* TextureBufferTripple::getBufferTexture() const
{
    return bufferTexture;
}
