#ifndef VECTOR4_H_
#define VECTOR4_H_

#include <QString>

#define GL3_PROTOTYPES 1
#include "graphics/gl3.h"

template <typename T, int XYZ, int W>
struct Vector4_T
{
public:

    T x;
    T y;
    T z;
    T w;

    /**
     * Initializes all components to 0.0f.
     */

    Vector4_T();

    Vector4_T(T x, T y);
    Vector4_T(T x, T y, T z);
    Vector4_T(T x, T y, T z, T w);

    QString toString(bool isVector = true) const;
};


template <typename T, int XYZ, int W>
Vector4_T<T, XYZ, W>::Vector4_T()
:   x(XYZ),
    y(XYZ),
    z(XYZ),
    w(W)
{
}


template <typename T, int XYZ, int W>
Vector4_T<T, XYZ, W>::Vector4_T(T x, T y)
:   x(x),
    y(y),
    z(XYZ),
    w(W)
{
}


template <typename T, int XYZ, int W>
Vector4_T<T, XYZ, W>::Vector4_T(T x, T y, T z)
:   x(x),
    y(y),
    z(z),
    w(W)
{
}


template <typename T, int XYZ, int W>
Vector4_T<T, XYZ, W>::Vector4_T(T x, T y, T z, T w)
:   x(x),
    y(y),
    z(z),
    w(w)
{
}


template <typename T, int XYZ, int W>
QString Vector4_T<T, XYZ, W>::toString(bool isVector) const
{
    QString s;

    if (isVector)
    {
        s += "(" + QString::number(x) + ", " + QString::number(y) + ", " + QString::number(z) + ", " + QString::number(w) + ")";
    }
    else
    {
        s += QString::number(x) + " " + QString::number(y) + " " + QString::number(z) + " " + QString::number(w);
    }

//    s += "(" + QString::number(x, 'f', 3) + ", " + QString::number(y, 'f', 3) + ", " + QString::number(z, 'f', 3) + ", " + QString::number(w, 'f', 3) + ")";


    return s;
}


typedef Vector4_T<GLfloat, 0, 1>  Vector4;
typedef Vector4_T<GLint, 0, 0>    Vector4i;

#endif /* VECTOR4_H_ */
