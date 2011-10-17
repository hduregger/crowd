#include <QString>

#include "Exception.h"


#define ERROR \
{ \
	Error::error(__FILE__, __LINE__); \
}

#define ERROR_MESSAGE(M) \
{ \
    Error::error(__FILE__, __LINE__, M); \
}

class Error
{
private:

	Error();
	virtual ~Error();

public:

	static void error(QString file, int line);
	static void error(QString file, int line, QString message);

};



inline void Error::error(QString file, int line)
{
    throw Exception(file + ":" + QString::number(line) + ": An error occurred. (Is any shader uniform variable unused?)");
}


inline void Error::error(QString file, int line, QString message)
{
    throw Exception(file + ":" + QString::number(line) + ": " + message);
}

