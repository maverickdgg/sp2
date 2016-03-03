/******************************************************************************/
/*!
\file	BB-8_2.cpp
\author Lee Jian Lin
\par	Email: 150580X\@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Contact Number: 9755 2038
\brief
This contains all of the functions in the second version of BB-8 class
*/
/******************************************************************************/
#include "BB-8_2.h"

size_t BB8v2::bb8v2_count = 0;
/******************************************************************************/
/*!
\brief
Second version of BB-8's default constructor implements count
*/
/******************************************************************************/
BB8v2::BB8v2()
{
	bb8v2_count++;
}
/******************************************************************************/
/*!
\brief
Second version of BB-8's overloaded constructor with parameters implements count
Sets the speed, rotating speed of BB-8's lower body as well as its' turn speed
\param
string object_name, int boundary, float viewAngle, Vector3 pos
*/
/******************************************************************************/
BB8v2::BB8v2(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	bb8v2_count++;
	speed = 50;
	turnSpeed = 30;
	lowerBodyRotate = 180;
}
/******************************************************************************/
/*!
\brief
Second version of BB-8's default destructor decrements count
*/
/******************************************************************************/
BB8v2::~BB8v2()
{
	bb8v2_count--;
}
/******************************************************************************/
/*!
\brief
Set the second version of BB-8 to move in circular motion using sin and cos as well as rotating while moving
\param
double dt
*/
/******************************************************************************/
void BB8v2::move(double dt)
{
	pos.x += cos(Math::DegreeToRadian(viewAngle)) * speed * dt;
	pos.z -= sin(Math::DegreeToRadian(viewAngle)) * speed * dt;
	lowerBodyRotate -= speed *dt;
}
/******************************************************************************/
/*!
\brief
Executing move function as well as rotation while moving
\param
double dt
*/
/******************************************************************************/
void BB8v2::moveCircles(double dt)
{
	viewAngle += turnSpeed * dt;
	move(dt);
}
/******************************************************************************/
/*!
\brief
ViewAngle is for turning speed, rotating at its own position without moving around
\param
double dt
*/
/******************************************************************************/
void BB8v2::rotateAbout(double dt)
{
	viewAngle += turnSpeed * dt;
}