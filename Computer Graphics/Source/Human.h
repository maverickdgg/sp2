/******************************************************************************/
/*!
\file	Human.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define Human type of NPCs
*/
/******************************************************************************/
#ifndef HUMAN_H
#define HUMAN_H
#include "GameChar.h"
/******************************************************************************/
/*!
Class Human:
\brief
Class for Human (Inheriting from GameChar)
/******************************************************************************/
class Human : public GameChar
{
public:
	Human();
	Human(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0), smaller init_Health = 0);
	~Human();
	static size_t h_count;
};
#endif