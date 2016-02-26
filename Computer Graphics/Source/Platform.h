#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameChar.h"

class Platform :public GameChar
{
public:
	Platform();
	Platform(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Platform();
	static size_t Platform_count;
	float lowerBodyRotate;
	float speed;
	float turnSpeed;
	void move(double dt);
	void moveCircles(double dt);
	void rotateAbout(double dt);

};
#endif