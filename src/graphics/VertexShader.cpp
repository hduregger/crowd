#include "VertexShader.h"
#include "../Exception.h"

VertexShader::VertexShader(const std::vector<QString>& filenames, const QString additionalSource)
:   Shader(filenames, additionalSource)
{
    shader = glCreateShader(GL_VERTEX_SHADER);

    if (shader == 0)
    {
        throw Exception("Could not create vertex shader object for " + getFilenamesString());
    }

    readSourceAndCompile(filenames);
}


VertexShader::~VertexShader()
{
    glDeleteShader(shader);
}
