#ifndef TEXTUREBUFFER_H_
#define TEXTUREBUFFER_H_


#include "Texture.h"

class BufferTexture : public Texture
{
public:
                BufferTexture();
    virtual     ~BufferTexture();

    /**
     * Attach the buffer texture to a buffer object.
     *
     * An internalFormat of GL_RGBA32F allows to access all 4 components with single fetch.
     * With GL_R32F a fetch in the fragment shader would only access 1 float.
     */

    void        attachToBufferObject(GLuint textureBuffer, GLenum internalFormat = GL_RGBA32F) const;
};

#endif /* TEXTUREBUFFER_H_ */
