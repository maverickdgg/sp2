#ifndef PINKKNIGHT_H
#define PINKKNIGHT_H
#include "GameChar.h"

class PinkKnight : public GameChar
{
public:
	PinkKnight();
	PinkKnight(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~PinkKnight();
	static size_t PinkKnight_count;
};
#endif