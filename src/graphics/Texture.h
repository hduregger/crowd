#ifndef TEXTURE_H_
#define TEXTURE_H_


#include <QImage>

#define GL3_PROTOTYPES 1
#include "gl3.h"

#include <vector>


class Texture
{
public:

    static const float  MAXIMUM_TEXEL_INTENSITY;


                    Texture(GLenum target);
    virtual         ~Texture();

    void            enable() const;
    void            disable() const;

    bool            isBufferTexture() const;

    /**
     * Loads the texture file and performs flipping and format conversion.
     */

    static QImage   loadTexture(QString filename, bool doMirrorX, bool doMirrorY);

    /**
     * Converts the image into a vector of floats.
     */

    static void     convertToFloats(QImage& image, std::vector<float>& data, size_t length);

    GLuint          getTexture();

protected:

    GLuint      texture;
    GLenum      target;
};

#endif /* TEXTURE_H_ */
