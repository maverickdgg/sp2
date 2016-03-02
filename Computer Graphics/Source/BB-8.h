/******************************************************************************/
/*!
\file	BB-8.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define a BB8 NPC inheriting from GameChar
*/
/******************************************************************************/
#ifndef BB_8_H
#define BB_8_H

#include "GameChar.h"

class BB8 :public GameChar
{
public:
	BB8();
	BB8(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~BB8();
	static size_t bb8_count;
	float lowerBodyRotate;
	float speed;
	float turnSpeed;
	void move(double dt);
	void moveCircles(double dt);
	void rotateAbout(double dt);
};
#endif