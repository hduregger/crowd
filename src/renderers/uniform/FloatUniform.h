#ifndef FLOAT_UNIFORM_H_
#define FLOAT_UNIFORM_H_

#define GL3_PROTOTYPES 1
#include "../../graphics/gl3.h"

#include "../../graphics/ShaderProgram.h"


class FloatUniform
{
public:
                    FloatUniform(ShaderProgram* shaderProgram, QString uniformName);
    virtual         ~FloatUniform();

    void            set(ShaderProgram* shaderProgram, GLfloat f) const;

private:


    GLint           uniform;
};

#endif /* FLOAT_UNIFORM_H_ */
