#ifndef CAMERA_H_
#define CAMERA_H_

class Camera
{
public:


    static const char*			CAMERA_PROJECTION;

    float   projection[16];


            Camera();
	virtual ~Camera();

    void    setOrthogonalProjection(float left, float right, float bottom, float top, float zNear, float zFar);

protected:

private:


};

#endif /* CAMERA_H_ */
