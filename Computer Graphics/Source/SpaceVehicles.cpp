#include "SpaceVehicles.h"

size_t SpaceVehicles::SV_count = 0;

SpaceVehicles::SpaceVehicles()
{
}

SpaceVehicles::SpaceVehicles(string object_name, int boundary, float viewAngle, Vector3 pos) : GameObject(object_name, boundary, viewAngle, pos)
{

}

SpaceVehicles::~SpaceVehicles()
{

}