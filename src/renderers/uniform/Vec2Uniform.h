#ifndef VEC2UNIFORM_H_
#define VEC2UNIFORM_H_

#define GL3_PROTOTYPES 1
#include "../../graphics/gl3.h"

#include "../../graphics/ShaderProgram.h"


class Vec2Uniform
{
public:
                Vec2Uniform(ShaderProgram* shaderProgram, QString uniformName);
    virtual     ~Vec2Uniform();


    void        set(ShaderProgram* shaderProgram, GLfloat x, GLfloat y) const;

private:

    GLint       uniform;
};

#endif /* VEC2UNIFORM_H_ */
