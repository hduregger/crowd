#ifndef NUMBERHELPER_H_
#define NUMBERHELPER_H_

#include <CL/cl.h>

template <typename T>
class NumberTemplate
{
public:

    static T    max(T a, T b);
    static T    min(T a, T b);

    static T    clamp(T minVal, T maxVal, T val);

    static T    length(T x, T y);
};

class Number
{
public:


    /**
     * Round up i to multiple of n.
     */

    static int  roundUpToMultiple(int i, int n);


    static void positionFromIndex(int i, int width, int* px, int* py);

    static int  indexFromPosition(int px, int py, int width, int components = 1);

    static bool isInside(int px, int py, int size);

    static bool isPowerOfTwo(size_t i);

    static cl_ulong nanoToMilliSecondsInteger(cl_ulong time);
    static cl_ulong nanoToMilliSecondsRemainder(cl_ulong time);
};


template <typename T>
inline T NumberTemplate<T>::max(T a, T b)
{
    return a > b ? a : b;
}


template <typename T>
inline T NumberTemplate<T>::min(T a, T b)
{
    return a < b ? a : b;
}


template <typename T>
inline T NumberTemplate<T>::clamp(T minVal, T maxVal, T val)
{
    return min(max(minVal, val), maxVal);
}

template <typename T>
inline T NumberTemplate<T>::length(T x, T y)
{
    return sqrt(x * x + y * y);
}


inline cl_ulong Number::nanoToMilliSecondsInteger(cl_ulong time)
{
    return time / 1000000;
}


inline cl_ulong Number::nanoToMilliSecondsRemainder(cl_ulong time)
{
    return time % 1000000;
}

#endif
