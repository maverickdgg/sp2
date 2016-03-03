/******************************************************************************/
/*!
\file	Sir.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define a Sir NPC inheriting from GameChar
*/
/******************************************************************************/
#ifndef SIR_H
#define SIR_H
#include "GameChar.h"

class Sir : public GameChar
{
	bool isTurned;
	float turnSpeed;
public:
	Sir();
	Sir(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Sir();
	void Salute(double dt);
};

#endif