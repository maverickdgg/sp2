#include "Buildings.h"

size_t Buildings::b_count = 0;

Buildings::Buildings()
{
	b_count++;
}

Buildings::Buildings(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	b_count++;
}

Buildings::~Buildings()
{
	b_count--;
}