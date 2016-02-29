#ifndef ALIEN_H
#define ALIEN_H
#include "GameChar.h"

class Alien : public GameChar
{
public:
	Alien();
	Alien(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0,0,0));
    ~Alien();
	static size_t alien_count;
	float f_scaleBig;
	bool b_scaleUp;

	void pulsingUpdate(double dt);
};
#endif