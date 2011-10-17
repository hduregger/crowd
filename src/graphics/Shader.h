#ifndef SHADER_H_
#define SHADER_H_

#include <QString>

#define GL3_PROTOTYPES 1
#include "gl3.h"

#include <vector>


/**
 * Abstract base class for shaders.
 */

class Shader
{
public:

                Shader(const std::vector<QString>& filenames, const QString additionalSource = "");
    virtual     ~Shader() = 0;

    QString     getInfoLog();
    GLint       getCompileStatus();

    GLuint      getShader();

    QString     getFilenamesString();


protected:

    GLuint                      shader;
    const std::vector<QString>  filenames;

    QString                     additionalSource;

    /**
     * Throws exception if compilation fails.
     */

    void        setSourceAndCompile(const std::vector<QByteArray>& sources);

    /**
     * Throws exception if compilation or file reading fails.
     */

    void        readSourceAndCompile(const std::vector<QString>& filenames);

};

#endif /* SHADER_H_ */
