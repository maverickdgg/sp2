#ifndef SPACE_VEHICLES_H
#define SPACE_VEHICLES_H
#include "GameObject.h"

class SpaceVehicles : public GameObject
{
public:
	SpaceVehicles();
	SpaceVehicles(string object_name, int boundary, float viewAngle, Vector3 pos);
	~SpaceVehicles();
	static size_t SV_count;
    int speed;
    void updateVehicle(bool isPressedW, bool isPressedS, bool isPressedA, bool isPressedD, float deltaTime);
private:
    int acceleration;
    float rotateAngle;
    smaller max_speed;
};
#endif