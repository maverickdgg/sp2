/******************************************************************************/
/*!
\file	Weapon.h
\author Lee Jian Lin
\par	Email: 150580X\@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define Weapon
*/
/******************************************************************************/
#ifndef WEAPON_H
#define WEAPON_H
#include "GameObject.h"
/******************************************************************************/
/*!
Class Weapon:
\brief
Class for the weapons inheriting from GameObject
*/
/******************************************************************************/
class Weapon : public GameObject
{
public:
	~Weapon();
	static size_t W_count;
	int dmg = 1;
	smaller attackSpeed = 1;
	float durability = 1.f;
protected:
	Weapon();
	Weapon(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
};
#endif