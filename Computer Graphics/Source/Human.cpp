#include "Human.h"

size_t Human::human_count = 0;

Human::Human()
{
	human_count++;
}

Human::Human(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	++human_count;
}

Human::~Human()
{
	--human_count;
}