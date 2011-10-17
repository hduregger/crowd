#include "GroupStatesRenderer.h"

#include "../graphics/OpenGL.h"
#include "../Error.h"


GroupStatesRenderer::GroupStatesRenderer(GLfloat viewportSize, const Texture* texture0, const Texture* texture1, const std::vector<QString>& vertexShaderFilenames, const std::vector<QString>& fragmentShaderFilenames, QString programName, bool isValueRenderer)
:   TextureRendererAlpha(viewportSize, texture0, vertexShaderFilenames, fragmentShaderFilenames, programName, isValueRenderer),
    texture1(texture1)
{
    GLint loc = shaderProgram->getUniformLocation("textureSampler1");

    // Set to texture image unit 1
    glUniform1i( loc, 1 );
    GL_ERROR;
}


GroupStatesRenderer::~GroupStatesRenderer()
{
}


void GroupStatesRenderer::render(int index)
{
    glActiveTexture(GL_TEXTURE1);
    texture1->enable();

    shaderProgram->enable();

    GLint loc = shaderProgram->getUniformLocation("index");

    glUniform1i( loc, index );
    GL_ERROR;

    TextureRendererAlpha::render();

    glActiveTexture(GL_TEXTURE1);
    texture1->disable();
}
