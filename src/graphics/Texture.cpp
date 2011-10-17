#include "Texture.h"

#include "OpenGL.h"


const float         Texture::MAXIMUM_TEXEL_INTENSITY = 255.0f;


Texture::Texture(GLenum target)
:   texture(0),
    target(target)
{
    glGenTextures(1, &texture);
    GL_ERROR;

    glBindTexture(target, texture);
    GL_ERROR;
}


Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}


void Texture::enable() const
{
    glBindTexture(target, texture);
    GL_ERROR;
}


void Texture::disable() const
{
    glBindTexture(target, 0);
    GL_ERROR;
}

bool Texture::isBufferTexture() const
{
    return target == GL_TEXTURE_BUFFER;
}


QImage Texture::loadTexture(QString filename, bool doMirrorX, bool doMirrorY)
{
    QImage image(filename);

    if (image.isNull())
    {
        throw Exception("Could not load \"" + filename + "\" as QImage");
    }

    if (image.format() != QImage::Format_ARGB32)
    {
        image = image.convertToFormat(QImage::Format_ARGB32);
    }

    image = image.mirrored(doMirrorX, doMirrorY);

    return image;
}


void Texture::convertToFloats(QImage& image, std::vector<float>& data, size_t pixelCount)
{
    QRgb* rgba = reinterpret_cast<QRgb*> (image.scanLine(0));

    size_t j = 0;

    for (size_t i = 0; i < pixelCount; i++)
    {
        data[j + 0] = (static_cast<float> ( qRed(   rgba[i]) )) / MAXIMUM_TEXEL_INTENSITY;
        data[j + 1] = (static_cast<float> ( qGreen( rgba[i]) )) / MAXIMUM_TEXEL_INTENSITY;
        data[j + 2] = (static_cast<float> ( qBlue(  rgba[i]) )) / MAXIMUM_TEXEL_INTENSITY;
        data[j + 3] = (static_cast<float> ( qAlpha( rgba[i]) )) / MAXIMUM_TEXEL_INTENSITY;

        j += 4;
    }
}


GLuint Texture::getTexture()
{
    return texture;
}
