#include "ChestBurster.h"

size_t ChestBurster::chestburster_count = 0;

ChestBurster::ChestBurster()
{
	chestburster_count++;
}

ChestBurster::ChestBurster(string object_name, int boundary, float viewAngle, Vector3 pos) : AlienEnemy(object_name, boundary, viewAngle, pos)
{
	chestburster_count++;
	speed = 50;
	turnSpeed = 60;
	lowerBodyRotate = 45;
	isTurned = false;
}

ChestBurster::~ChestBurster()
{
	chestburster_count--;
}

void ChestBurster::translateWorm(double dt)
{
	/*viewAngle += turnSpeed * dt;
	if (viewAngle > 45)
		isTurned = true;
	if (isTurned == true)
	{

	}*/
	if (isTurned == false)
	{
		viewAngle += turnSpeed*dt;
		if (viewAngle > 25)
		{
			isTurned = true;
		}
	}
	else if (isTurned == true)
	{
		viewAngle -= turnSpeed*dt;
		if (viewAngle < -25)
		{
			isTurned = false;
		}
	}
}