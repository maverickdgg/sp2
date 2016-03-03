/******************************************************************************/
/*!
\file	Alien.h
\author Wayne Aw
\par	Email: 152558X\@mymail.nyp.edu.sg
\par	Admin Number: 152558X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1504
\brief
Class to define alien while inheriting from GameChar
*/
/******************************************************************************/
#ifndef ALIEN_H
#define ALIEN_H
#include "GameChar.h"

/******************************************************************************/
/*!
Class Alien:
\brief	Providing the AlienEnemies to move ( inherits from Alien )
/******************************************************************************/
class Alien : public GameChar
{
public:
	Alien();
	Alien(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Alien();
	static size_t alien_count;
	float f_scaleBig;
	bool b_scaleUp;


	void pulsingUpdate(double dt);
};
#endif