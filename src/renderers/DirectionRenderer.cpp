#include "DirectionRenderer.h"

#include "../graphics/OpenGL.h"
#include "../Error.h"


DirectionRenderer::DirectionRenderer(GLfloat                     viewportSize,
                                     const Texture*              texture,
                                     const Texture2D*            legend,
                                     const Texture2D*            arrow,
                                     const std::vector<QString>& vertexShaderFilenames,
                                     const std::vector<QString>& fragmentShaderFilenames,
                                     QString                     programName)
:   TextureRenderer(viewportSize, texture, vertexShaderFilenames, fragmentShaderFilenames, programName, false),
    legend(legend),
    arrow(arrow)
{
    GLint loc = shaderProgram->getUniformLocation("legend");

    // Set to texture image unit 1
    glUniform1i( loc, 1 );
    GL_ERROR;

    loc = shaderProgram->getUniformLocation("arrow");

    // Set to texture image unit 2
    glUniform1i( loc, 2 );
    GL_ERROR;


    uniformScale = shaderProgram->getUniformLocation("scale");

    glUniform1f( uniformScale, 1.0f );
    GL_ERROR;

    // Set domain size

    loc = shaderProgram->getUniformLocation("domainSize");

    glUniform1ui( loc, viewportSize );
    GL_ERROR;
}


DirectionRenderer::~DirectionRenderer()
{
}


void DirectionRenderer::render()
{
     glActiveTexture(GL_TEXTURE1);
     legend->enable();

     glActiveTexture(GL_TEXTURE2);
     arrow->enable();

     TextureRenderer::render();

     glActiveTexture(GL_TEXTURE2);
     arrow->disable();

     glActiveTexture(GL_TEXTURE1);
     legend->disable();
}


void DirectionRenderer::setScale(float scale)
{
    shaderProgram->enable();

    glUniform1f( uniformScale, scale );
    GL_ERROR;
}
