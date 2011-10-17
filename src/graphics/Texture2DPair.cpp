#include "Texture2DPair.h"

#include "OpenGL.h"
#include "../computation/OpenCL.h"


Texture2DPair::Texture2DPair(   GLsizei         width,
                                GLsizei         height,
                                GLint           wrapMode,
                                GLint           minificationFilter,
                                GLint           magnificationFilter,
                                GLint           internalFormat,
                                GLenum          format,
                                GLenum          type,
                                const GLvoid*   data,
                                cl_mem_flags    flags,
                                const Context*   context)
:   image(NULL),
    texture(NULL)
{
    texture = new Texture2D(width, height, wrapMode, minificationFilter, magnificationFilter, internalFormat, format, type, data);

    cl_int status;

    image = clCreateFromGLTexture2D(context->context, flags, GL_TEXTURE_2D, 0, texture->getTexture(), &status);
    CL_ERROR(status);
}


Texture2DPair::~Texture2DPair()
{
    clReleaseMemObject(image);
    delete texture;
}

cl_mem Texture2DPair::getImageShared() const
{
    return image;
}


const Texture2D* Texture2DPair::getTexture2D() const
{
    return texture;
}
