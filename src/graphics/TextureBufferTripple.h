#ifndef SHAREDTEXTUREBUFFERTRIPPLE_H_
#define SHAREDTEXTUREBUFFERTRIPPLE_H_

#include <CL/cl.h>
#include <CL/cl_gl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"
#include "../computation/Context.h"

#include "BufferTexture.h"

/**
 * Provides an OpenGL texture buffer object with a shared reference for OpenCL and an
 * attached buffer texture for access to the buffer in a shader.
 */

class TextureBufferTripple
{
public:
                                /**
                                 * Usage e.g. DYNAMIC_COPY.
                                 * InternalFormat e.g. GL_RGBA32F.
                                 * Flags e.g. CL_MEM_READ_WRITE.
                                 */

                                TextureBufferTripple(GLsizeiptr     size,
                                                     const void*    data,
                                                     GLenum         usage,
                                                     GLenum         internalFormat,
                                                     cl_mem_flags   flags,
                                                     const Context* context);
    virtual                     ~TextureBufferTripple();

    GLuint                      getBuffer() const;
    cl_mem                      getBufferShared() const;
    const BufferTexture*        getBufferTexture() const;

private:

    GLuint                      buffer;
    cl_mem                      bufferShared;
    BufferTexture*              bufferTexture;
};

#endif /* SHAREDTEXTUREBUFFERTRIPPLE_H_ */
