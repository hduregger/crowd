#include "String.h"

#include "Number.h"

String::String()
{
}

String::~String()
{
}


QString String::getStringList(const std::vector<QString>& strings)
{
    QString stringList = "{";

    std::vector<QString>::const_iterator iter;

    for (iter = strings.begin(); iter != strings.end(); ++iter)
    {
        stringList += *iter;

        if (iter < strings.end() - 1)
        {
            stringList += ", ";
        }
    }

    stringList += "}";

    return stringList;
}


QString String::formatProfilingString(ProfilingElement profilingElement)
{
    QChar zero = QChar('0');

    QString s = QString("%1 %2 ns %3 ns %4 ns")
                 .arg(profilingElement.name + ":", -30)
                 .arg(profilingElement.queuedAverage, 12, 10, zero)
                 .arg(profilingElement.startAverage,  12, 10, zero)
                 .arg(profilingElement.endAverage,    12, 10, zero);

    //
    // Check for valid timings. Due to queue handling and batched command processing
    // AMD returns weird start and end times. If one does not guard profiled commands
    // with clFinish statements it is possible to get invalid (negative) timings.
    //

    if (    (profilingElement.queuedAverage > profilingElement.startAverage)
         || (profilingElement.startAverage  > profilingElement.endAverage  ) )
    {
        s += " INVALID TIMES";
    }

    return s;

}


//QString String::formatProfilingString(QString name, cl_ulong waitTime, cl_ulong executionTime)
QString String::formatProfilingString(QString name, cl_ulong, cl_ulong executionTime)
{
    QChar zero = QChar('0');

  //  if (waitTime == 0)
    {
         return QString("%1 %2.%3 ms")
                 .arg(name + ":", -30)
                 .arg(Number::nanoToMilliSecondsInteger(executionTime), 5)
                 .arg(Number::nanoToMilliSecondsRemainder(executionTime), 6, 10, zero);
    }
 /*   else
    {
         return QString("%1 %2.%3 ms %4.%5 ms")
                 .arg(name + ":", -30)
                 .arg(Number::nanoToMilliSecondsInteger(executionTime), 5)
                 .arg(Number::nanoToMilliSecondsRemainder(executionTime), 6, 10, zero)
                 .arg(Number::nanoToMilliSecondsInteger(waitTime), 5)
                 .arg(Number::nanoToMilliSecondsRemainder(waitTime), 6, 10, zero);
    }*/
}


QString String::formatMemoryString(QString name, int size)
{
    return QString("%1 %2").arg(name, -30).arg(size, 12);
}


QString String::degree()
{
    ushort degree = (ushort) 0xB0;

    QString deg = QString::fromUtf16(&degree, 1);

    return deg;
}


const GLchar* String::getCharPointer(const QString s)
{
    return reinterpret_cast<const GLchar*>( s.toAscii().data() );
}


const GLchar* String::getCharPointer(const QByteArray array)
{
    return reinterpret_cast<const GLchar*>( array.constData() );
}
