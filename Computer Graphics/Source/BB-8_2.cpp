#include "BB-8_2.h"

size_t BB8v2::bb8v2_count = 0;

BB8v2::BB8v2()
{
	bb8v2_count++;
}

BB8v2::BB8v2(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	bb8v2_count++;
	speed = 50;
	turnSpeed = 30;
	lowerBodyRotate = 180;
}

BB8v2::~BB8v2()
{
	bb8v2_count--;
}
void BB8v2::move( double dt)
{
	pos.x += cos(Math::DegreeToRadian(viewAngle)) * speed * dt;
	pos.z -= sin(Math::DegreeToRadian(viewAngle)) * speed * dt;
	lowerBodyRotate -= speed *dt;
}

void BB8v2::moveCircles(double dt)
{
	viewAngle += turnSpeed * dt;
	move(dt);
}

void BB8v2::rotateAbout(double dt)
{
	viewAngle += turnSpeed * dt;
	//move(dt);
}