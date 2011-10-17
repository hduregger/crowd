#include "Exception.h"


Exception::Exception()
{
}


Exception::Exception(QString message)
: message(message)
{
}


Exception::~Exception() throw ()
{
}


Exception::Exception(const Exception& e)
{
    message = e.message;
}


Exception& Exception::operator=(const Exception& e)
{
    if (this != &e)
    {
        message = e.message;
    }

    return *this;
}
