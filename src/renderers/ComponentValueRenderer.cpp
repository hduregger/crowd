#include "ComponentValueRenderer.h"

ComponentValueRenderer::ComponentValueRenderer( GLfloat                       viewportSize,
                                                const Texture*                valueTexture,
                                                const Texture2D*              legend,
                                                const std::vector<QString>&   vertexShaderFilenames,
                                                const std::vector<QString>&   fragmentShaderFilenames,
                                                QString                       programName,
                                                bool                          isValueRenderer)
:   ValueRenderer(viewportSize, valueTexture, legend, vertexShaderFilenames, fragmentShaderFilenames, programName, isValueRenderer),
    uniformComponent(NULL)
{

    uniformComponent = new UnsignedIntegerUniform(shaderProgram, "component");
    setComponent(0);
}


ComponentValueRenderer::~ComponentValueRenderer()
{
    delete uniformComponent;
}


void ComponentValueRenderer::setComponent(GLuint component) const
{
    uniformComponent->set(shaderProgram, component);
}
