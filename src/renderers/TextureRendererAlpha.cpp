#include "TextureRendererAlpha.h"

#include "../graphics/OpenGL.h"
#include "../Error.h"


TextureRendererAlpha::TextureRendererAlpha(GLfloat viewportSize, const Texture* texture, const std::vector<QString>& vertexShaderFilenames, const std::vector<QString>& fragmentShaderFilenames, QString programName, bool isValueRenderer)
:   TextureRenderer(viewportSize, texture, vertexShaderFilenames, fragmentShaderFilenames, programName, isValueRenderer)
{
    alpha = new FloatUniform(shaderProgram, "alpha");
}


TextureRendererAlpha::~TextureRendererAlpha()
{
    delete alpha;
}


void TextureRendererAlpha::setAlpha(GLfloat f)
{
    alpha->set(shaderProgram, f);
}
