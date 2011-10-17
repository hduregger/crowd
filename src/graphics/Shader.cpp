#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QString>
#include <QDebug>

#include <fstream>
#include <vector>

#include "Shader.h"

#include "OpenGL.h"
#include "../String.h"

using namespace std;


Shader::Shader(const std::vector<QString>& filenames, const QString additionalSource)
:   filenames(filenames),
    additionalSource(additionalSource)
{
}


Shader::~Shader()
{
}


GLuint Shader::getShader()
{
    return shader;
}


GLint Shader::getCompileStatus()
{
    GLint success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    GL_ERROR;

    return success;
}


QString Shader::getInfoLog()
{
    QString log;

    GLint infologLength = 0;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

    GL_ERROR;

    if (infologLength > 0)
    {
        std::vector<GLchar> infoLog(infologLength);

        glGetShaderInfoLog(shader, infologLength, NULL, &infoLog.at(0));

        GL_ERROR;

        log += &infoLog.at(0);
    }

    return log;
}


void Shader::readSourceAndCompile(const std::vector<QString>& filenames)
{
    std::vector<QString>::const_iterator iter;

    std::vector<QByteArray> sources;

    sources.push_back((QString("#version 410\n") + additionalSource).toAscii());

    for (iter = filenames.begin(); iter != filenames.end(); ++iter)
    {
        QFile file(*iter);

        if (!file.open(QFile::ReadOnly))
        {
            throw Exception("Could not open file " + (*iter) + " for reading program source");
        }

        sources.push_back(file.readAll());
    }

    setSourceAndCompile(sources);
}


void Shader::setSourceAndCompile(const std::vector<QByteArray>& sources)
{
    std::vector<const GLchar*> pointers;
    std::vector<GLint> lengths;

    std::vector<QByteArray>::const_iterator iter;

    for (iter = sources.begin(); iter != sources.end(); ++iter)
    {
        pointers.push_back(String::getCharPointer(*iter));
        lengths.push_back((*iter).size());
    }

    glShaderSource( shader, pointers.size(), &pointers.at(0), &lengths.at(0) );

    glCompileShader(shader);

    // Verify successful compilation

    GLint params;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &params );

    if (params == GL_FALSE)
    {
        throw Exception("Shader compilation failed: " + getFilenamesString() + ":\n" + getInfoLog());
    }
}


QString Shader::getFilenamesString()
{
    return String::getStringList(filenames);
}
