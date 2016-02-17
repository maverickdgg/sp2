#include "Human.h"

size_t Human::h_count = 0;

Human::Human()
{
	h_count++;
}

Human::Human(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	++h_count;
}

Human::~Human()
{
	--h_count;
}