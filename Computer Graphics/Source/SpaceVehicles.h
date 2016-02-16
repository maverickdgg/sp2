#ifndef SPACE_VEHICLES_H_H
#define SPACE_VEHICLES_H_H
#include "GameObject.h"

class SpaceVehicles : public GameObject
{
public:
	SpaceVehicles();
	SpaceVehicles(string object_name, int boundary, float viewAngle, Vector3 pos);
	~SpaceVehicles();
	static size_t SV_count;
};

#endif