#include "GradientRenderer.h"

#include "../graphics/OpenGL.h"
#include "../Error.h"


GradientRenderer::GradientRenderer( GLfloat                     viewportSize,
                                    const Texture2D*            gradient01,
                                    const Texture2D*            gradient23,
                                    const Texture2D*            legend,
                                    const Texture2D*            arrow,
                                    const std::vector<QString>& vertexShaderFilenames,
                                    const std::vector<QString>& fragmentShaderFilenames,
                                    QString                     programName)
:   DirectionRenderer(viewportSize, gradient01, legend, arrow, vertexShaderFilenames, fragmentShaderFilenames, programName),
    gradientTexture23(gradient23),
    component(NULL),
    pass(NULL),
    alpha(NULL),
    isInterpolating(false)
{

    GLint loc;

    loc = shaderProgram->getUniformLocation("textureSampler23");

    // Set to texture image unit 3
    glUniform1i( loc, 3 );
    GL_ERROR;

    component = new UnsignedIntegerUniform(shaderProgram, "component");
    component->set(shaderProgram, 0u);

    pass = new UnsignedIntegerUniform(shaderProgram, "pass");
    pass->set(shaderProgram, 0u);

    alpha = new FloatUniform(shaderProgram, "alpha");
    alpha->set(shaderProgram, 0.0f);
}


GradientRenderer::~GradientRenderer()
{
    delete component;
    delete pass;
    delete alpha;
}


void GradientRenderer::render()
{
    //
    // Render interpolated gradient field with color legend
    //

    pass->set(shaderProgram, 0u);

    glActiveTexture(GL_TEXTURE0);
    texture->enable();

    GLint param;

    if (isInterpolating)
    {
        param = GL_LINEAR;
    }
    else
    {
        param = GL_NEAREST;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);

    glActiveTexture(GL_TEXTURE3);
    gradientTexture23->enable();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);

    DirectionRenderer::render();

    //
    // Render arrows based on nearest texel
    //

    pass->set(shaderProgram, 1u);

    glActiveTexture(GL_TEXTURE0);
    texture->enable();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glActiveTexture(GL_TEXTURE3);
    gradientTexture23->enable();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glEnable(GL_BLEND);
    GL_ERROR;

    DirectionRenderer::render();

    glDisable(GL_BLEND);
    GL_ERROR;

    glActiveTexture(GL_TEXTURE3);
    gradientTexture23->disable();
}


void GradientRenderer::setComponent(GLuint component) const
{
    this->component->set(shaderProgram, component);
}


void GradientRenderer::setAlpha(GLfloat alpha) const
{
    this->alpha->set(shaderProgram, alpha);
}


void GradientRenderer::setIsInterpolating(bool isInterpolating)
{
    this->isInterpolating = isInterpolating;
}
