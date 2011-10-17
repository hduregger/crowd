#ifndef TEXTURERENDERERALPHA_H_
#define TEXTURERENDERERALPHA_H_

#include "TextureRenderer.h"

#include "uniform/FloatUniform.h"


class TextureRendererAlpha : public TextureRenderer
{
public:
                TextureRendererAlpha(GLfloat viewportSize, const Texture* texture, const std::vector<QString>& vertexShaderFilenames, const std::vector<QString>& fragmentShaderFilenames, QString programName, bool isValueRenderer);
    virtual     ~TextureRendererAlpha();

    void        setAlpha(GLfloat f);

private:

    FloatUniform* alpha;

};

#endif /* TEXTURERENDERERALPHA_H_ */
