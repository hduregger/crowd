#include "Mat4Uniform.h"


#include "../../graphics/OpenGL.h"
#include "../../Error.h"


Mat4Uniform::Mat4Uniform(ShaderProgram* shaderProgram, QString uniformName)
:   uniform(-1)
{
    uniform = shaderProgram->getUniformLocation(uniformName);
}


Mat4Uniform::~Mat4Uniform()
{
}


void Mat4Uniform::set(ShaderProgram* shaderProgram, GLfloat* matrix) const
{
    shaderProgram->enable();

    glUniformMatrix4fv(uniform, 1, GL_FALSE, matrix);
    GL_ERROR;
}
