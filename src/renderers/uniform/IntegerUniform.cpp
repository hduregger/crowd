#include "IntegerUniform.h"

#include "../../graphics/OpenGL.h"
#include "../../Error.h"


IntegerUniform::IntegerUniform(ShaderProgram* shaderProgram, QString uniformName)
:   uniform(-1)
{
    uniform = shaderProgram->getUniformLocation(uniformName);
}


IntegerUniform::~IntegerUniform()
{
}


void IntegerUniform::set(ShaderProgram* shaderProgram, GLint i) const
{
    shaderProgram->enable();

    glUniform1i(uniform, i);
    GL_ERROR;
}
