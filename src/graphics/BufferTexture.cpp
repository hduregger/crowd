#include "BufferTexture.h"

#include "OpenGL.h"


BufferTexture::BufferTexture()
:   Texture(GL_TEXTURE_BUFFER)
{
}


BufferTexture::~BufferTexture()
{
}


void BufferTexture::attachToBufferObject(GLuint textureBuffer, GLenum internalFormat) const
{
    glTexBuffer(target, internalFormat, textureBuffer);
    GL_ERROR;
}
