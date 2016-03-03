/******************************************************************************/
/*!
\file	PinkKnight.h
\author Wayne Aw
\par	Email: 152558X@mymail.nyp.edu.sg
\par	Admin Number: 152558X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1504
\brief
Class to define PinkKnight while inheriting from GameChar
*/
/******************************************************************************/
#ifndef PINKKNIGHT_H
#define PINKKNIGHT_H
#include "GameChar.h"
/******************************************************************************/
/*!
Class PinkKnight:
\brief
Class for PinkKnight (Inheriting from GameChar)
/******************************************************************************/
class PinkKnight : public GameChar
{
public:
	PinkKnight();
	PinkKnight(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~PinkKnight();
	static size_t PinkKnight_count;
};
#endif