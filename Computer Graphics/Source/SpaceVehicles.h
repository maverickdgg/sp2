#ifndef SPACE_VEHICLES_H
#define SPACE_VEHICLES_H
#include "GameObject.h"
#include "Application.h"
#include "Player.h"

class SpaceVehicles : public GameObject
{
public:
	SpaceVehicles();
	SpaceVehicles(string object_name, int boundary, float viewAngle, Vector3 pos);
	~SpaceVehicles();
	static size_t SV_count;
    float speed;
	bool b_isInVehicle;
	bool b_vehDebounce;
    void updateVehicle(double deltaTime);
	void enterVehicleUpdate(Player& player);
	float rotationZ;
private:
    float acceleration;
    float rotateAngle;
    int max_speed;
	
};
#endif