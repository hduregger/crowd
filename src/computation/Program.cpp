#include "Program.h"

#include <QFile>
#include <vector>

#include "OpenCL.h"
#include "../String.h"


Program::Program(const QString               sourceFile,
                 const Context*              context,
                 const QString               additionalOptions)
:   sourceFile(sourceFile),
    program(NULL),
    context(context)
{
    readSourceAndCompile(additionalOptions);
}


Program::~Program()
{
    clReleaseProgram(program);
}


void Program::readSourceAndCompile(const QString additionalOptions)
{
    QByteArray source;

    QFile file(sourceFile);

    if (!file.open(QFile::ReadOnly))
    {
        throw Exception("Could not open file " + sourceFile + " for reading program source");
    }

    source = file.readAll();

    setSourceAndCompile(source, additionalOptions);
}


void Program::setSourceAndCompile(const QByteArray source, const QString additionalOptions)
{
    cl_int status;

    std::vector<const char*> pointers;

    const char* pointer = String::getCharPointer(source);
    size_t length = source.size();

    program = clCreateProgramWithSource(context->context, 1, &pointer, &length, &status);

    QString optionsString = "-Werror -I./src/kernels/ " + additionalOptions;

    const char* options = String::getCharPointer(optionsString);

    status = clBuildProgram(program, 1, &context->device, options, NULL, NULL);

    if (status != CL_SUCCESS)
    {
        cl_build_status buildStatus;

        status = clGetProgramBuildInfo(program, context->device, CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &buildStatus, NULL);
        CL_ERROR(status);

        if (buildStatus != CL_BUILD_SUCCESS)
        {
            throw Exception(getSourceFile() + ": OpenCL program build log:\n  " + getInfoLog(context->device, program));
        }
    }
}


QString Program::getBuildStatusMessage(cl_device_id deviceId, cl_program program, cl_build_status buildStatus)
{
    QString message;

    switch (buildStatus)
    {
        case CL_BUILD_NONE:
        {
            message = "CL_BUILD_NONE";
            break;
        }

        case CL_BUILD_ERROR:
        {
            message = "CL_BUILD_ERROR:\n";
            message += "Log:\n" + getInfoLog(deviceId, program) + "\n";

            break;
        }

        case CL_BUILD_SUCCESS:
        {
            message = "CL_BUILD_SUCCESS";
            break;
        }

        case CL_BUILD_IN_PROGRESS:
        {
            message = "CL_BUILD_IN_PROGRESS";
            break;
        }

        default:
        {
            message = "Undefined build status";
            break;
        }
    }

    return message;
}


QString Program::getInfoLog(cl_device_id deviceId, cl_program program)
{
    QString log;

    cl_int status;

    size_t length;

    status = clGetProgramBuildInfo(program, deviceId, CL_PROGRAM_BUILD_LOG, 0, NULL, &length);
    CL_ERROR(status);

    std::vector<char> logString(length);

    status = clGetProgramBuildInfo(program, deviceId, CL_PROGRAM_BUILD_LOG, length, &logString.at(0), NULL);
    CL_ERROR(status);

    log += &logString.at(0);

    return log;
}


cl_program Program::getProgram()
{
    return program;
}


QString Program::getSourceFile()
{
    return sourceFile;
}
