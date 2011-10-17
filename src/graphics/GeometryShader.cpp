#include "GeometryShader.h"
#include "../Exception.h"

GeometryShader::GeometryShader(const std::vector<QString>& filenames, const QString additionalSource)
:   Shader(filenames, additionalSource)
{
    shader = glCreateShader(GL_GEOMETRY_SHADER);

    if (shader == 0)
    {
        throw Exception("Could not create geometry shader object for " + getFilenamesString());
    }

    readSourceAndCompile(filenames);
}

GeometryShader::~GeometryShader()
{
    glDeleteShader(shader);
}
