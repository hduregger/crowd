#ifndef OPENCLHELPER_H_
#define OPENCLHELPER_H_

#include <QString>

#include "../Exception.h"

#include <CL/cl.h>




#define CL_ERROR(arg) OpenCL::checkError((arg), __FILE__, __LINE__);


class OpenCL
{
private:

	                OpenCL();
	virtual         ~OpenCL();

public:

	static void     checkError(cl_int code, QString file, int line);
	static QString  getCode(cl_int code);

};


inline void OpenCL::checkError(cl_int code, QString file, int line)
{
    if (code != CL_SUCCESS)
    {
        throw Exception( "OpenCL error in " + file + ":" + QString::number(line) + ": " + QString(OpenCL::getCode(code)) );
    }
}

#endif /* OPENCLHELPER_H_ */
