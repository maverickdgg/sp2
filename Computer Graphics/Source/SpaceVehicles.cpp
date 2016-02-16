#include "SpaceVehicles.h"

size_t SpaceVehicles::SV_count = 0;

SpaceVehicles::SpaceVehicles(string name, float viewAngle, float posX, float posY) : GameObject(name, viewAngle, posX, posY)
{

}

SpaceVehicles::~SpaceVehicles()
{

}