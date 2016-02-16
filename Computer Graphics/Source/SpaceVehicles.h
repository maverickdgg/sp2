#ifndef SPACE_VEHICLES_H_H
#define SPACE_VEHICLES_H_H
#include "GameObject.h"

class SpaceVehicles : public GameObject
{
public:
	SpaceVehicles(string object_name, float viewAngle = 0, float positionX = 0, float positionY = 0);
	~SpaceVehicles();
	static size_t SV_count;
};

#endif