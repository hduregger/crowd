#ifndef OPENGLHELPER_H_
#define OPENGLHELPER_H_

#include <QApplication>
#include <QString>

#define GL3_PROTOTYPES 1
#include "gl3.h"

#include "../Exception.h"

#include <GL/glu.h>



#define GL_ERROR \
{ \
	OpenGL::checkError(__FILE__, __LINE__); \
}



class OpenGL
{
private:

	                    OpenGL();
	virtual             ~OpenGL();

public:

	static QString      getVersion();

	static void         checkError(QString file, int line);

	static QString      getFramebufferStatusString(GLenum status);

};


inline void OpenGL::checkError(QString file, int line)
{
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
        throw Exception( "OpenGL error in " + file + ":" + QString::number(line) + ": " + QString((GLchar*) gluErrorString(error)) );
	}
}


#endif /* OPENGLHELPER_H_ */
