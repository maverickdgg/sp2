#ifndef CHESTBURSTER_H
#define CHESTBURSTER_H

#include "AlienEnemy.h"

class ChestBurster : public AlienEnemy
{
public:
	ChestBurster();
	ChestBurster(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~ChestBurster();
	static size_t chestburster_count;
	bool isTurned;
	float lowerBodyRotate;
	float speed;
	float turnSpeed;
	void translateWorm(double dt);
};

#endif