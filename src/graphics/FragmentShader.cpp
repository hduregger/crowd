#include "FragmentShader.h"
#include "../Exception.h"

FragmentShader::FragmentShader(const std::vector<QString>& filenames, const QString additionalSource)
:   Shader(filenames, additionalSource)
{
    shader = glCreateShader(GL_FRAGMENT_SHADER);

    if (shader == 0)
    {
        throw Exception("Could not create fragment shader object for " + getFilenamesString());
    }

    readSourceAndCompile(filenames);
}


FragmentShader::~FragmentShader()
{
    glDeleteShader(shader);
}
