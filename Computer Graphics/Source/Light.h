/******************************************************************************/
/*!
\file	Light.h
\author Lee Jian Lin
\par	Email: 150580X\@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Struct to define Light
*/
/******************************************************************************/
#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vertex.h"
/******************************************************************************/
/*!
Struct Light:
\brief
Struct for Light
*/
/******************************************************************************/
struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	Light()
	{
		position.Set(0, 0, 0);
		color.Set(1, 1, 1);
		power = 0.1f;
		kC = kL = kQ = 1;
	}

	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
};

#endif