#include "OpenGL.h"



OpenGL::OpenGL()
{
}

OpenGL::~OpenGL()
{
}


QString OpenGL::getVersion()
{
    const GLubyte* s = glGetString(GL_VERSION);
	GL_ERROR;

	return QString(reinterpret_cast<const char*>(s));
}


QString OpenGL::getFramebufferStatusString(GLenum status)
{
    switch (status)
    {
        default:
        {
            return "Unknown OpenGL framebuffer status";
            break;
        }

#define CASE(arg) \
case arg: \
{ \
    return #arg; \
    break; \
}

        CASE(GL_FRAMEBUFFER_COMPLETE)
        CASE(GL_FRAMEBUFFER_UNDEFINED)
        CASE(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
        CASE(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
        CASE(GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
        CASE(GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
        CASE(GL_FRAMEBUFFER_UNSUPPORTED)
        CASE(GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
        CASE(GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)
    }
}


