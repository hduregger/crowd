#include "Vec2Uniform.h"

#include "../../graphics/OpenGL.h"
#include "../../Error.h"


Vec2Uniform::Vec2Uniform(ShaderProgram* shaderProgram, QString uniformName)
:   uniform(-1)
{
    uniform = shaderProgram->getUniformLocation(uniformName);
}


Vec2Uniform::~Vec2Uniform()
{
}


void Vec2Uniform::set(ShaderProgram* shaderProgram, GLfloat x, GLfloat y) const
{
    shaderProgram->enable();

    float v[2] = { x, y };

    glUniform2fv(uniform, 1, v);
    GL_ERROR;
}
