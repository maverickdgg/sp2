#ifndef CAMERA_TPS_H
#define CAMERA_TPS_H

#include "Camera.h"

class CameraTPS : public Camera
{
public:
    float cameraRotationX;
    float cameraRotationY;
	Vector3 defaultOffset;
    Vector3 defaultUp;
    Vector3 right;
    Vector3 view;
    CameraTPS();
    ~CameraTPS();
    virtual void Init(const Vector3& pos, const Vector3& up, const Vector3& vehiclePos);
    void tpsUpdateRotation(float speed);
    void tpsUpdateVec(Vector3 targetedVec);
};

#endif