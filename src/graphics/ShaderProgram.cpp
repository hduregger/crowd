#include "ShaderProgram.h"
#include "../Exception.h"
#include "OpenGL.h"
#include "../String.h"

#include <vector>



ShaderProgram::ShaderProgram(QString name)
: name(name)
{
    program = glCreateProgram();

    if (program == 0)
    {
        throw Exception("Could not create shader program '" + name + "'");
    }
}


ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(program);
}


GLuint ShaderProgram::getProgram()
{
    return program;
}


void ShaderProgram::link()
{
    // NOTE: this has no effect with AMD when done like as "fragmentData[0]" for an array (probably fixed by now)
    glBindFragDataLocation(program, 0, "fragmentData0");
    glBindFragDataLocation(program, 1, "fragmentData1");
    glBindFragDataLocation(program, 2, "fragmentData2");
    GL_ERROR;

    glLinkProgram(program);
    GL_ERROR;

    // Verify successful linking

    GLint params;
    glGetProgramiv( program, GL_LINK_STATUS, &params );

    if (params == GL_FALSE)
    {
        throw Exception(name + ": " + getInfoLog());
    }
}


void ShaderProgram::attach(Shader* shader)
{
    glAttachShader(program, shader->getShader());
    GL_ERROR;
}


void ShaderProgram::detach(Shader* shader)
{
    glDetachShader(program, shader->getShader());
    GL_ERROR;
}



GLint ShaderProgram::getLinkStatus()
{
    GLint success;

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    GL_ERROR;

    return success;
}


QString ShaderProgram::getInfoLog()
{
    QString log;

    GLint infologLength = 0;

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);

    GL_ERROR;

    if (infologLength > 0)
    {
        std::vector<GLchar> infoLog(infologLength);


        glGetProgramInfoLog(program, infologLength, NULL, &infoLog.at(0));

        GL_ERROR;

        log += &infoLog.at(0);
    }

    return log;
}


void ShaderProgram::enable()
{
    glUseProgram(program);
    GL_ERROR;
}


GLint ShaderProgram::getUniformLocation(QString name)
{
    GLint location = glGetUniformLocation( program, String::getCharPointer(name) );
    GL_ERROR;

    if (location == -1)
    {
        throw Exception("Could not locate uniform with name '" + name + "' in '" + this->name + "'");
    }

    return location;
}


GLint ShaderProgram::getAttribLocation(QString name)
{
    GLint location = glGetAttribLocation( program, String::getCharPointer(name) );
    GL_ERROR;

    if ( location == -1 )
    {
        throw Exception("Could not locate attribute with name '" + name + "' in '" + this->name + "'");
    }

    return location;
}


QString ShaderProgram::getName()
{
    return name;
}
