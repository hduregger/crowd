#ifndef INTEGER_UNIFORM_H_
#define INTEGER_UNIFORM_H_

#define GL3_PROTOTYPES 1
#include "../../graphics/gl3.h"

#include "../../graphics/ShaderProgram.h"


class IntegerUniform
{
public:
                    IntegerUniform(ShaderProgram* shaderProgram, QString uniformName);
    virtual         ~IntegerUniform();

    void            set(ShaderProgram* shaderProgram, GLint i) const;

private:


    GLint           uniform;
};

#endif /* INTEGER_UNIFORM_H_ */
