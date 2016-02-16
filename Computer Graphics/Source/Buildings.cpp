#include "Buildings.h"

size_t Buildings::count = 0;

Buildings::Buildings(string name, float viewAngle, float posX, float posY) : GameObject(name, viewAngle, posX, posY)
{
	Buildings_count = 0;
}

Buildings::~Buildings()
{

}