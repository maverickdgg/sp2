#include "Pingu.h"

size_t Pingu::pingu_count = 0;

Pingu::Pingu()
{
	pingu_count++;
}

Pingu::Pingu(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	pingu_count++;
}

Pingu::~Pingu()
{
	pingu_count--;
}