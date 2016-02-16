#include "Human.h"

size_t Human::count = 0;

Human::Human(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
}

Human::~Human()
{

}