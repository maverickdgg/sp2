#ifndef ALIENENEMY_H
#define ALIENENEMY_H
#include "Alien.h"

class AlienEnemy : public Alien
{
	bool isTurned;
	float turnSpeed;
public:
	AlienEnemy();
	AlienEnemy(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~AlienEnemy();
	void translateWorm(double dt);
	void move(double dt);
	float wormtranslating;
	float wormrotating;
	float wormtranslate;
	float wormrotate;
};

#endif