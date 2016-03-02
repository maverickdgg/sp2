/******************************************************************************/
/*!
\file	Platform.cpp
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Contact Number: 9755 2038
\brief
This contains all of the functions in Platform Class
*/
/******************************************************************************/
#include "Platform.h"

size_t Platform::Platform_count = 0;
/******************************************************************************/
/*!
\brief
Platform's default constructor implements count
*/
/******************************************************************************/
Platform::Platform()
{
	Platform_count++;
}
/******************************************************************************/
/*!
\brief
Platform's overloaded constructor with parameters implements count
\param
string object_name, int boundary, float viewAngle, Vector3 pos
*/
/******************************************************************************/
Platform::Platform(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	Platform_count++;
	speed = 50;
	turnSpeed = 30;
	lowerBodyRotate = 180;
}
/******************************************************************************/
/*!
\brief
Platform's default destructor decrements count
*/
/******************************************************************************/
Platform::~Platform()
{
	Platform_count--;
}
/******************************************************************************/
/*!
\brief
Sets the movement of the Platform (To be edited)
\param
double dt
*/
/******************************************************************************/
void Platform::move(double dt)
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
void Platform::moveCircles(double dt)
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
void Platform::rotateAbout(double dt)
{
	viewAngle += turnSpeed * dt;
	//move(dt);
}
/*<---Samuel--->*/
void Platform::changePlatform(bool& isClimb, Platform& p, Player& player)
{
	if (isClimb == false && collision(p.pos, player.pos, 46))
	{
		p.boundary = 10;
	}
	else if (isClimb == true && collision(p.pos, player.pos, 46))
	{
		//player.pos.z += 2;
		player.pos.y += 4;
	}
}

void Platform::noLadderPlatform(Platform& p, Player& player)
{
    if (collision(p.pos, player.pos, 46))
    {
        p.boundary = 10;
    }
}