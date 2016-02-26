#include "Sir.h"

Sir::Sir()
{

}

Sir::Sir(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	turnSpeed = 45;
	isTurned = false;
}

Sir::~Sir()
{

}

void Sir::Salute(double dt)
{
	if (isTurned == false)
	{
		viewAngle += turnSpeed*dt;
		if (viewAngle > 90)
		{
			isTurned = true;
		}
	}
	else if (isTurned == true)
	{
		viewAngle -= turnSpeed*dt;
		if (viewAngle < -90)
		{
			isTurned = false;
		}
	}
}