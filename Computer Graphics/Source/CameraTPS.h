/******************************************************************************/
/*!
\file	CameraTPS.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define the second type of camera
*/
/******************************************************************************/
#ifndef CAMERA_TPS_H
#define CAMERA_TPS_H

#include "Camera.h"
#include "GameObject.h"
/******************************************************************************/
/*!
Class CameraTPS:
\brief
Class for the third type of camera (Inheriting from Camera)
/******************************************************************************/
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