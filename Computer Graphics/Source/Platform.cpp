#include "Platform.h"

size_t Platform::Platform_count = 0;

Platform::Platform()
{
	Platform_count++;
}

Platform::Platform(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	Platform_count++;
	speed = 50;
	turnSpeed = 30;
	lowerBodyRotate = 180;
}

Platform::~Platform()
{
	Platform_count--;
}
void Platform::move(double dt)
{
	pos.x += cos(Math::DegreeToRadian(viewAngle)) * speed * dt;
	pos.z -= sin(Math::DegreeToRadian(viewAngle)) * speed * dt;
	lowerBodyRotate -= speed *dt;
}

void Platform::moveCircles(double dt)
{
	viewAngle += turnSpeed * dt;
	move(dt);
}

void Platform::rotateAbout(double dt)
{
	viewAngle += turnSpeed * dt;
	//move(dt);
}