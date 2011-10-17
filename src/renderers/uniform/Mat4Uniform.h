#ifndef MAT4UNIFORM_H_
#define MAT4UNIFORM_H_

#define GL3_PROTOTYPES 1
#include "../../graphics/gl3.h"

#include "../../graphics/ShaderProgram.h"


class Mat4Uniform
{
public:
                    Mat4Uniform(ShaderProgram* shaderProgram, QString uniformName);
    virtual         ~Mat4Uniform();

    void            set(ShaderProgram* shaderProgram, GLfloat* matrix) const;

private:

    GLint           uniform;
};

#endif /* MAT4UNIFORM_H_ */
