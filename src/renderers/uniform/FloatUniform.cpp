#include "FloatUniform.h"

#include "../../graphics/OpenGL.h"
#include "../../Error.h"


FloatUniform::FloatUniform(ShaderProgram* shaderProgram, QString uniformName)
:   uniform(-1)
{
    uniform = shaderProgram->getUniformLocation(uniformName);
}


FloatUniform::~FloatUniform()
{
}


void FloatUniform::set(ShaderProgram* shaderProgram, GLfloat f) const
{
    shaderProgram->enable();

    glUniform1f(uniform, f);
    GL_ERROR;
}
