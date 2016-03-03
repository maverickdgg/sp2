/******************************************************************************/
/*!
\file	Medic.h
\author Wayne Aw
\par	Email: 152558X@mymail.nyp.edu.sg
\par	Admin Number: 152558X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1504
\brief
Class to define Medic NPC while inheriting from GameChar
*/
/******************************************************************************/
#ifndef MEDIC_H
#define MEDIC_H
#include "GameChar.h"

/******************************************************************************/
/*!
Class Medic:
\brief	Class for the medic NPC
*/
/******************************************************************************/
class Medic : public GameChar
{
public:
	Medic();
	Medic(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Medic();
	static size_t medic_count;
};
#endif