#include "Texture2D.h"

#include "OpenGL.h"


Texture2D::Texture2D(   GLsizei         width,
                        GLsizei         height,
                        GLint           wrapMode,
                        GLint           minificationFilter,
                        GLint           magnificationFilter,
                        GLint           internalFormat,
                        GLenum          format,
                        GLenum          type,
                        const GLvoid*   data)
:   Texture(GL_TEXTURE_2D),
    width(width),
    height(height)
{
    glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magnificationFilter);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minificationFilter);
    GL_ERROR;

    glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, data);
    GL_ERROR;

    if (    (minificationFilter == GL_NEAREST_MIPMAP_NEAREST)
         || (minificationFilter == GL_NEAREST_MIPMAP_LINEAR)
         || (minificationFilter == GL_LINEAR_MIPMAP_NEAREST)
         || (minificationFilter == GL_LINEAR_MIPMAP_LINEAR) )
    {
        glGenerateMipmap(GL_TEXTURE_2D);
        GL_ERROR;
    }

    disable();
}


Texture2D::~Texture2D()
{
}


void Texture2D::attachToActiveFramebuffer(GLenum colorAttachment) const
{
    disable();

    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, colorAttachment, target, texture, 0);
    GL_ERROR;
}


GLsizei Texture2D::getWidth() const
{
    return width;
}


GLsizei Texture2D::getHeight() const
{
    return height;
}
