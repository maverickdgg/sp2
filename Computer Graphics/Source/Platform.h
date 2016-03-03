/******************************************************************************/
/*!
\file	Platform.h
\author Lee Jian Lin
\par	Email: 150580X\@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define platform while inheriting from GameChar
*/
/******************************************************************************/
#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameChar.h"
#include "Player.h"
/******************************************************************************/
/*!
Class Platform:
\brief
Class for Platform (Inheriting from GameChar)
/******************************************************************************/
class Platform :public GameChar
{
public:
	Platform();
	Platform(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Platform();
	static size_t Platform_count;
	float lowerBodyRotate;
	float speed;
	float turnSpeed;
	void move(double dt);
	void moveCircles(double dt);
	void rotateAbout(double dt);
	void changePlatform(bool& isClimb, Platform& p, Player& player);
    void noLadderPlatform(Platform& p, Player& player);
};
#endif