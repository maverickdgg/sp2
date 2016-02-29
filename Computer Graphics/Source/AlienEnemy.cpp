#include "AlienEnemy.h"

AlienEnemy::AlienEnemy()
{

}

AlienEnemy::AlienEnemy(string object_name, int boundary, float viewAngle, Vector3 pos) : Alien(object_name, boundary, viewAngle, pos)
{
	turnSpeed = 45;
	isTurned = false;
	wormtranslate = wormrotate = false;
	wormtranslating = wormrotating = 0;
}

AlienEnemy::~AlienEnemy()
{

}

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