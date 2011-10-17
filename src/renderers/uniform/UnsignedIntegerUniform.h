#ifndef UNSIGNED_INTEGER_UNIFORM_H_
#define UNSIGNED_INTEGER_UNIFORM_H_

#define GL3_PROTOTYPES 1
#include "../../graphics/gl3.h"

#include "../../graphics/ShaderProgram.h"

class UnsignedIntegerUniform
{
public:
                    UnsignedIntegerUniform(ShaderProgram* shaderProgram, QString uniformName);
    virtual         ~UnsignedIntegerUniform();

    void            set(ShaderProgram* shaderProgram, GLuint i) const;

private:


    GLint           uniform;
};

#endif /* UNSIGNED_INTEGER_UNIFORM_H_ */
