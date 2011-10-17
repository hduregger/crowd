#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include "Shader.h"

class ShaderProgram
{
public:
                ShaderProgram(QString name);
    virtual     ~ShaderProgram();

    void        attach(Shader* shader);
    void        detach(Shader* shader);

    void        link();

    QString     getInfoLog();

    GLint       getLinkStatus();

    /**
     * Throws an exception if there is no uniform with the given name.
     */

    GLint       getUniformLocation(QString name);

    /**
     * Throws an exception if there is no attribute with the given name.
     */

    GLint       getAttribLocation(QString name);

    GLuint      getProgram();

    void        enable();

    QString     getName();


private:

    GLuint      program;
    QString     name;
};

#endif /* SHADERPROGRAM_H_ */
