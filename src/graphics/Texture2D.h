#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_

#include "Texture.h"


class Texture2D : public Texture
{
public:
                Texture2D(  GLsizei         width,
                            GLsizei         height,
                            GLint           wrapMode,
                            GLint           minificationFilter,
                            GLint           magnificationFilter,
                            GLint           internalFormat,
                            GLenum          format,
                            GLenum          type,
                            const GLvoid*   data);
    virtual     ~Texture2D();

    GLsizei     getWidth() const;
    GLsizei     getHeight() const;


    void        attachToActiveFramebuffer(GLenum colorAttachment) const;

private:

    GLsizei     width;
    GLsizei     height;

};

#endif /* TEXTURE2D_H_ */
