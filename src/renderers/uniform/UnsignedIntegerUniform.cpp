#include "UnsignedIntegerUniform.h"

#include "../../graphics/OpenGL.h"
#include "../../Error.h"


UnsignedIntegerUniform::UnsignedIntegerUniform(ShaderProgram* shaderProgram, QString uniformName)
:   uniform(-1)
{
    uniform = shaderProgram->getUniformLocation(uniformName);
}


UnsignedIntegerUniform::~UnsignedIntegerUniform()
{
}


void UnsignedIntegerUniform::set(ShaderProgram* shaderProgram, GLuint i) const
{
    shaderProgram->enable();

    glUniform1ui(uniform, i);
    GL_ERROR;
}
