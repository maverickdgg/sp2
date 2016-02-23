#include "PinkKnight.h"

size_t PinkKnight::PinkKnight_count = 0;

PinkKnight::PinkKnight()
{
	PinkKnight_count++;
}

PinkKnight::PinkKnight(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	PinkKnight_count++;
}

PinkKnight::~PinkKnight()
{
	PinkKnight_count--;
}