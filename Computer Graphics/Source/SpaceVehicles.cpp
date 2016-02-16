#include "SpaceVehicles.h"

size_t SpaceVehicles::SV_count = 0;

SpaceVehicles::SpaceVehicles(string object_name, int boundary, float viewAngle, Vector3 pos) : GameObject(object_name, boundary, viewAngle, pos)
{
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	SV_count++;
}

SpaceVehicles::~SpaceVehicles()
{
	SV_count--;
}