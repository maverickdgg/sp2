#ifndef ALIENENEMY_H
#define ALIENENEMY_H
#include "Alien.h"

class AlienEnemy : public Alien
{
public:
	AlienEnemy();
	AlienEnemy(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~AlienEnemy();
	static size_t alienEnemy_count;
};

#endif