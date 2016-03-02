/******************************************************************************/
/*!
\file	Sir.cpp
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Contact Number: 9755 2038
\brief
This contains all of the functions in Sir class
*/
/******************************************************************************/
#include "Sir.h"
/******************************************************************************/
/*!
\brief
Sir's default constructor
*/
/******************************************************************************/
Sir::Sir()
{

}
/******************************************************************************/
/*!
\brief
Sir's overloaded constructor with parameters as well as turning speed and boolen isTurned being set to false
\param
string object_name, int boundary, flaot viewAngle, Vector3 pos
*/
/******************************************************************************/
Sir::Sir(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	turnSpeed = 45;
	isTurned = false;
}
/******************************************************************************/
/*!
\brief
Sir's default destructor
*/
/******************************************************************************/
Sir::~Sir()
{

}
/******************************************************************************/
/*!
\brief
Sir NPC will rotate his arm from -90 degrees to 90 degress and repeat the cycle
\param
double dt
*/
/******************************************************************************/
void Sir::Salute(double dt)
{
	if (isTurned == false)
	{
		viewAngle += turnSpeed*dt;
		if (viewAngle > 90)
		{
			isTurned = true;
		}
	}
	else if (isTurned == true)
	{
		viewAngle -= turnSpeed*dt;
		if (viewAngle < -90)
		{
			isTurned = false;
		}
	}
}