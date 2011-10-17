#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <QString>
#include <QByteArray>

#include <CL/cl.h>

#include <vector>

#include "Context.h"


class Program
{
public:
                    Program(const QString               sourceFile,
                            const Context*              context,
                            const QString               additionalOptions);
    virtual         ~Program();

    static QString  getBuildStatusMessage(cl_device_id deviceId, cl_program program, cl_build_status buildStatus);
    static QString  getInfoLog(cl_device_id deviceId, cl_program program);

    cl_program      getProgram();

    QString         getSourceFile();

private:

    const QString               sourceFile;

    cl_program                  program;
    const Context*              context;

    void            readSourceAndCompile(const QString additionalOptions);
    void            setSourceAndCompile(const QByteArray source, const QString additionalOptions);
};

#endif /* PROGRAM_H_ */
