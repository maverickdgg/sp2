/******************************************************************************/
/*!
\file	AlienEnemy.h
\author Wayne Aw
\par	Email: 152558X@mymail.nyp.edu.sg
\par	Admin Number: 152558X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1504
\brief
Functions of Alien
*/
/******************************************************************************/
#include "Alien.h"

size_t Alien::alien_count = 0;

/******************************************************************************/
/*!
\brief
Alien's default constructor implements count
*/
/******************************************************************************/
Alien::Alien()
{
	alien_count++;
}

/******************************************************************************/
/*!
\brief
Overloaded constructor with parameters
\param object_name - name of alien
\param int boundary - boundary of the alien
\param float viewAngle 
\param Vector3 pos - Appoints the xyz position of the alien
*/
/******************************************************************************/
Alien::Alien(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	alien_count++;
	b_scaleUp = true;
	f_scaleBig = 0;
}

/******************************************************************************/
/*!
\brief
Alien's default destructor decrements count
*/
/******************************************************************************/
Alien::~Alien()
{
	alien_count--;
}


/******************************************************************************/
/*!
\brief
Logic of the alien
*/
/******************************************************************************/
void Alien::pulsingUpdate(double dt)
{
	if (b_scaleUp == true)
	{
		f_scaleBig += dt;
	}
	else
	{
		f_scaleBig -= dt;
		if (f_scaleBig < 0)
		{
			f_scaleBig = 0;
		}
	}
	if (f_scaleBig >3)
	{
		b_scaleUp = false;
	}
	else if (f_scaleBig <= 0)
	{
		b_scaleUp = true;
	}
}