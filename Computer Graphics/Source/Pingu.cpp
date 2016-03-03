/******************************************************************************/
/*!
\file	Pingu.cpp
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Contact Number: 9755 2038
\brief
This contains all of the functions in Pingu class
*/
/******************************************************************************/
#include "Pingu.h"

size_t Pingu::pingu_count = 0;
/******************************************************************************/
/*!
\brief
Pingu's default constructor implements count
*/
/******************************************************************************/
Pingu::Pingu()
{
	pingu_count++;
}
/******************************************************************************/
/*!
\brief
Pingu's overloaded constructor with parameters implements count
\param
string object_name, int boundary, float viewAngle, Vector3 pos
*/
/******************************************************************************/
Pingu::Pingu(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	pingu_count++;
}
/******************************************************************************/
/*!
\brief
Pingu's default destructor decrements count
*/
/******************************************************************************/
Pingu::~Pingu()
{
	pingu_count--;
}