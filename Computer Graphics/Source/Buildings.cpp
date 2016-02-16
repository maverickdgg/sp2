#include "Buildings.h"

size_t Buildings::b_count = 0;

Buildings::Buildings(string name, float viewAngle, float posX, float posY) : GameObject(name, viewAngle, posX, posY)
{
}

Buildings::~Buildings()
{

}