#ifndef BB_8_V2_H
#define BB_8_V2_H

#include "GameChar.h"

class BB8v2 :public GameChar
{
public:
	BB8v2();
	BB8v2(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~BB8v2();
	static size_t bb8v2_count;
	float lowerBodyRotate;
	float speed;
	float turnSpeed;
	void move(double dt);
	void moveCircles(double dt);
	void rotateAbout(double dt);

};
#endif