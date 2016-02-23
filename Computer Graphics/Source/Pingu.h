#ifndef PINGU_H
#define PINGU_H

#include "GameChar.h"

class Pingu :public GameChar
{
public:
	Pingu();
	Pingu(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Pingu();
	static size_t pingu_count;
};
#endif