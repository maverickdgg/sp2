/******************************************************************************/
/*!
\file	Alien.h
\author Wayne Aw
\par	Email: 152558X@mymail.nyp.edu.sg
\par	Admin Number: 152558X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1504
\brief
Class to define alien while inheriting from GameChar
*/
/******************************************************************************/
#include "Medic.h"

size_t Medic::medic_count = 0;

/******************************************************************************/
/*!
\brief
Medic's default constructor implements count
*/
/******************************************************************************/
Medic::Medic()
{
	medic_count++;
}
/******************************************************************************/
/*!
\brief
Overloaded constructor with parameters
\param object_name - name of Medic
\param int boundary - Boundary of the Medic
\param float viewAngle
\param Vector3 pos - Appoints the xyz position of the Medic
*/
/******************************************************************************/
Medic::Medic(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	medic_count++;
}

/******************************************************************************/
/*!
\brief
Medic's default destructor decrements count
*/
/******************************************************************************/
Medic::~Medic()
{
	medic_count--;
}