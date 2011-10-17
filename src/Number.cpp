#include "Number.h"


int Number::roundUpToMultiple(int i, int n)
{
    if (n == 0)
    {
        return i;
    }

    int remainder = i % n;

    if (remainder == 0)
    {
        return i;
    }

    return i + n - remainder;
}


void Number::positionFromIndex(int i, int width, int* px, int* py)
{
    *px = i % width;
    *py = i / width;
}


int Number::indexFromPosition(int px, int py, int width, int components)
{
    int i;

    i = px * components + py * width * components;

    return i;
}


bool Number::isInside(int px, int py, int size)
{
    return ( (px >= 0) && (px < size) && (py >= 0) && (py < size) );
}


bool Number::isPowerOfTwo(size_t i)
{
    // ~i + 1 == two's complement representation for -i

    return ( i & (~i + 1) ) == i;
}

