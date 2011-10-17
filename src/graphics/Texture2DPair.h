#ifndef TEXTURE2DPAIR_H_
#define TEXTURE2DPAIR_H_

#include <CL/cl.h>
#include <CL/cl_gl.h>

#define GL3_PROTOTYPES 1
#include "../graphics/gl3.h"


#include "Texture2D.h"
#include "../computation/Context.h"


class Texture2DPair
{
public:
                        /**
                         * InternalFormat e.g. GL_RGBA32F.
                         * Flags e.g. CL_MEM_READ_WRITE.
                         */

                        Texture2DPair(  GLsizei         width,
                                        GLsizei         height,
                                        GLint           wrapMode,
                                        GLint           minificationFilter,
                                        GLint           magnificationFilter,
                                        GLint           internalFormat,
                                        GLenum          format,
                                        GLenum          type,
                                        const GLvoid*   data,
                                        cl_mem_flags    flags,
                                        const Context*  context);
    virtual             ~Texture2DPair();

    cl_mem              getImageShared() const;
    const Texture2D*    getTexture2D() const;

private:

    cl_mem              image;
    Texture2D*          texture;
};

#endif /* TEXTURE2DPAIR_H_ */
