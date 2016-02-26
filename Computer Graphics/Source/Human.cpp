#include "Human.h"

size_t Human::h_count = 0;

Human::Human()
{
	h_count++;
}

Human::Human(string object_name, int boundary, float viewAngle, Vector3 pos, smaller init_Health) : GameChar(object_name, boundary, viewAngle, pos, init_Health)
{
	++h_count;
}

Human::~Human()
{
	--h_count;
}