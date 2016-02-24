#include "BB-8.h"

size_t BB8::bb8_count = 0;

BB8::BB8()
{
	bb8_count++;
}

BB8::BB8(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	bb8_count++;
	speed = 50;
	turnSpeed = 20;
	lowerBodyRotate = 0;
}

BB8::~BB8()
{
	bb8_count--;
}
void BB8::move( double dt)
{
	pos.x += cos(Math::DegreeToRadian(viewAngle)) * speed * dt;
	pos.z -= sin(Math::DegreeToRadian(viewAngle)) * speed * dt;
	lowerBodyRotate += speed *dt;
}

void BB8::moveCircles(double dt)
{
	viewAngle += turnSpeed * dt;
	move(dt);
}
