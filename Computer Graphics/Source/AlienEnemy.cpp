/******************************************************************************/
/*!
\file	AlienEnemy.h
\author Wayne Aw
\par	Email: 152558X\@mymail.nyp.edu.sg
\par	Admin Number: 152558X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1504
\brief
Functions of AlienEnemy
*/
/******************************************************************************/
#include "AlienEnemy.h"

/****************************************************************************/
/*!
\brief
default constructor for AlienEnemy
*/
/****************************************************************************/
AlienEnemy::AlienEnemy()
{
}

/****************************************************************************/
/*!
\brief
Setting the speed and translation of up and down
\param object_name - name of alien
\param int boundary - boundary of the alien
\param float viewAngle
\param Vector3 pos - Appoints the xyz position of the alien

/****************************************************************************/
AlienEnemy::AlienEnemy(string object_name, int boundary, float viewAngle, Vector3 pos) : Alien(object_name, boundary, viewAngle, pos)
{
	turnSpeed = 45;
	isTurned = false;
	wormtranslate = wormrotate = false;
	wormtranslating = wormrotating = 0;
}
/******************************************************************************/
/*!
\brief
AlienEnemy's default destructor decrements count
*/
/******************************************************************************/
AlienEnemy::~AlienEnemy()
{

}
/******************************************************************************/
/*!
\brief
This makes the worm go up and down
\param double dt - To be put in update()
*/
/******************************************************************************/
void AlienEnemy::translateWorm(double dt)
{
	if (isTurned == false)
	{
		viewAngle += turnSpeed*dt;
		if (viewAngle > 10)
		{
			isTurned = true;
		}
	}
	else if (isTurned == true)
	{
		viewAngle -= turnSpeed*dt;
		if (viewAngle < -10)
		{
			isTurned = false;
		}
	}
}
/******************************************************************************/
/*!
\brief
This allows the worm to move forward to a specific location and then rotate 180 degrees to backtrack. (non - stop)
\param double dt - To be put in update()
*/
/******************************************************************************/
void AlienEnemy::move(double dt)
{
	if (wormtranslate == false)
	{
		wormtranslating += 20 * (dt);
		if (wormtranslating > 25)
		{
			wormtranslate = true;
			wormrotating = 180;
		}
	}
	else if (wormtranslate == true)
	{
		wormtranslating -= 20 * (dt);
		if (wormtranslating < -25)
		{
			wormtranslate = false;
			wormrotating -= 180;
		}
	}
}