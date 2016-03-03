/******************************************************************************/
/*!
\file	Camera3.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define the third type of camera
*/
/******************************************************************************/
#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
/******************************************************************************/
/*!
Class Camera3:
\brief
Class for the third type of camera (Inheriting from Camera)
/******************************************************************************/
class Camera3 : public Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	float CameraSpeed;
	float cameraRotationX;
	float cameraRotationY;
	Vector3 view;
	Vector3 right;
	float f_jumpSpeed;
	float f_jumpAcceleration;
	bool b_jumping;
	bool b_jumpUP;
	float movementSpeed;
	float boundaryX;
	float boundaryZ;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up, float boundX, float boundZ);
	void updateRotation(float CameraSpeed);
	void updateRotationTps(float cameraSpeed);
	void tpsUpdate(Camera3 cam, double dt);
	virtual void Update(double dt);
	virtual void Reset();
};
#endif