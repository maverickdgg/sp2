#include "SpaceVehicles.h"

size_t SpaceVehicles::count = 0;

SpaceVehicles::SpaceVehicles(string name, float viewAngle, float posX, float posY) : GameObject(name, viewAngle, posX, posY)
{
	SpaceVehicles_count = 0;
}

SpaceVehicles::~SpaceVehicles()
{

}