#ifndef CAMERA_TPS_H
#define CAMERA_TPS_H

#include "Camera.h"
#include "GameObject.h"

class CameraTPS : public Camera
{
public:
	float cameraRotationX;
	float cameraRotationY;
	Vector3 defaultOffset;

    Vector3 defaultUp;
    Vector3 right;
    Vector3 view;
	GameObject* targetObj;
	bool b_cameraLock;
	bool b_cameraLockDebounce;
    CameraTPS();
    ~CameraTPS();
    virtual void Init(const Vector3& pos, const Vector3& up, GameObject* targetObj);
    void tpsUpdateRotation(float speed);
    void tpsUpdateVec(double dt);

};

#endif