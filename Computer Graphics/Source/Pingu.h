/******************************************************************************/
/*!
\file	Pingu.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define Pingu NPC inheriting from GameChar
*/
/******************************************************************************/
#ifndef PINGU_H
#define PINGU_H

#include "GameChar.h"
/******************************************************************************/
/*!
Class BB8:
\brief
Class for the Pingu NPC ( Inherits from GameChar )
*/
/******************************************************************************/
class Pingu :public GameChar
{
public:
	Pingu();
	Pingu(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Pingu();
	static size_t pingu_count;
};
#endif