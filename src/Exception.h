#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <QString>

class Exception : public std::exception
{
public:

    QString		message;

	            Exception();
	            Exception(QString message);

	virtual     ~Exception() throw ();


	            Exception(const Exception& e);

	Exception&  operator=(const Exception& e);

};

#endif /* EXCEPTION_H_ */
