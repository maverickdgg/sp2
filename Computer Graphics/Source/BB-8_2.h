/******************************************************************************/
/*!
\file	BB-8_2.h
\author Lee Jian Lin
\par	Email: 150580X\@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define another version of BB-8 NPC inheriting from GameChar
*/
/******************************************************************************/
#ifndef BB_8_V2_H
#define BB_8_V2_H

#include "GameChar.h"
/******************************************************************************/
/*!
Class BB8:
\brief
Class for the second version of BB8 NPC ( Inherits from GameChar )
*/
/******************************************************************************/
class BB8v2 :public GameChar
{
public:
	BB8v2();
	BB8v2(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~BB8v2();
	static size_t bb8v2_count;
	float lowerBodyRotate;
	float speed;
	float turnSpeed;
	void move(double dt);
	void moveCircles(double dt);
	void rotateAbout(double dt);

};
#endif