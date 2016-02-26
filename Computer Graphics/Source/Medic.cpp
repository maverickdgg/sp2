#include "Medic.h"

size_t Medic::medic_count = 0;

Medic::Medic()
{
	medic_count++;
}

Medic::Medic(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	medic_count++;
}

Medic::~Medic()
{
	medic_count--;
}