#include "SystemTime.h"


SystemTime::SystemTime()
{
}


SystemTime::~SystemTime()
{
}


cl_ulong SystemTime::getTime()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return static_cast<cl_ulong> (ts.tv_sec * 1000000000) + static_cast<cl_ulong> (ts.tv_nsec);
}


cl_float SystemTime::getTimeSeconds()
{
    cl_ulong ns = getTime();

    return static_cast<cl_float> (ns) / 1000000000.0f;
}
