#ifndef TIMEHELPER_H_
#define TIMEHELPER_H_

#include <time.h>
#include <CL/cl.h>


class SystemTime
{
public:

    static cl_ulong getTime();
    static cl_float getTimeSeconds();


private:
                    SystemTime();
    virtual         ~SystemTime();
};

#endif /* TIMEHELPER_H_ */
