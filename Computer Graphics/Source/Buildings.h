/******************************************************************************/
/*!
\file	Buildings.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define the Buildings inheriting from GameChar
*/
/******************************************************************************/
#ifndef BUILDINGS_H
#define BUILDINGS_H
#include "GameChar.h"
#include "Player.h"
/******************************************************************************/
/*!
Class Buildings:
\brief
Class for the Buildings ( Inherits from GameChar )
/******************************************************************************/
class Buildings : public GameChar
{
public:
	Buildings();
	Buildings(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Buildings();
	static size_t b_count;
	vector<GameObject> allOBJS;
	void climb(bool& isClimb, Buildings& ladder, Player& player);
};
#endif