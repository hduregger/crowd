#include "ValueRenderer.h"

#include "../graphics/OpenGL.h"
#include "../Error.h"


ValueRenderer::ValueRenderer(GLfloat                       viewportSize,
                             const Texture*                valueTexture,
                             const Texture2D*              legend,
                             const std::vector<QString>&   vertexShaderFilenames,
                             const std::vector<QString>&   fragmentShaderFilenames,
                             QString                       programName,
                             bool                          isValueRenderer)
:   TextureRenderer(viewportSize, valueTexture, vertexShaderFilenames, fragmentShaderFilenames, programName, isValueRenderer),
    uniformColorScaleMin(NULL),
    uniformColorScaleMax(NULL),
    colorScaleMin(0),
    colorScaleMax(100),
    legend(legend)
{
    uniformColorScaleMin = new FloatUniform(shaderProgram, "colorScaleMin");
    uniformColorScaleMax = new FloatUniform(shaderProgram, "colorScaleMax");
    setColorScaleMin(colorScaleMin);
    setColorScaleMax(colorScaleMax);


    GLint loc = shaderProgram->getUniformLocation("legend");

    // Set to texture image unit 1
    glUniform1i( loc, 1 );
    GL_ERROR;
}


ValueRenderer::~ValueRenderer()
{
    delete uniformColorScaleMin;
    delete uniformColorScaleMax;
}


void ValueRenderer::setColorScaleMin(float min)
{
    colorScaleMin = min;

    uniformColorScaleMin->set(shaderProgram, min);
}


void ValueRenderer::setColorScaleMax(float max)
{
    colorScaleMax = max;

    uniformColorScaleMax->set(shaderProgram, max);
}


float ValueRenderer::getColorScaleMin() const
{
    return colorScaleMin;
}


float ValueRenderer::getColorScaleMax() const
{
    return colorScaleMax;
}


void ValueRenderer::render()
{
    glActiveTexture(GL_TEXTURE1);
    GL_ERROR;
    legend->enable();

    TextureRenderer::render();

    glActiveTexture(GL_TEXTURE1);
    GL_ERROR;
    legend->disable();
}
