#include "Camera.h"

#include <cmath>
#include <cassert>

#include "../Exception.h"

const char*			Camera::CAMERA_PROJECTION = "camera.projection";


Camera::Camera()
{
}

Camera::~Camera()
{
}


void Camera::setOrthogonalProjection(float left, float right, float bottom, float top, float zNear, float zFar)
{
    if (left == right)
    {
        throw Exception("Camera left and right match!");
    }

    if (bottom == top)
    {
        throw Exception("Camera bottom and top match!");
    }

    if (zNear >= zFar)
    {
        throw Exception("Camera zNear >= zFar!");
    }

	float rl = right - left;
	float tb = top - bottom;
	float fn = zFar - zNear;

	float tx = -(right + left) / rl;
	float ty = -(top + bottom) / tb;
	float tz = -(zFar + zNear) / fn;

	for (int i = 0; i < 16; i++)
	{
		projection[i] = 0.0f;
	}

	projection[ 0] = 2.0f / rl;
	projection[ 5] = 2.0f / tb;
	projection[10] = -2.0f / fn;
	projection[12] = tx;
	projection[13] = ty;
	projection[14] = tz;
	projection[15] = 1.0f;
}
