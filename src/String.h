#ifndef UTILILTYSTRING_H_
#define UTILILTYSTRING_H_

#include <QString>
#include <vector>
#include <CL/cl.h>

#define GL3_PROTOTYPES 1
#include "graphics/gl3.h"


#include "computation/ProfilingElement.h"


class String
{
public:

    static  QString getStringList(const std::vector<QString>& strings);

    static  QString formatProfilingString(ProfilingElement profilingElement);
    static  QString formatProfilingString(QString name, cl_ulong waitTime, cl_ulong executionTime);
    static  QString formatMemoryString(QString name, int size);

    /**
     * Returns the degree symbol as QString.
     */

    static  QString degree();

    static  const GLchar* getCharPointer(const QString s);
    static  const GLchar* getCharPointer(const QByteArray array);

private:
                String();
    virtual     ~String();
};

#endif /* UTILILTYSTRING_H_ */
