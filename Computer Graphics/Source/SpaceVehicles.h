#ifndef SPACE_VEHICLES_H
#define SPACE_VEHICLES_H
#include "GameObject.h"
#include "Application.h"
#include "Player.h"
#include "Map.h"

#include <queue>

using std::queue;

class SpaceVehicles : public GameObject
{
public:
	SpaceVehicles();
	SpaceVehicles(string object_name, int boundary, float viewAngle, Vector3 pos,int max_speed = 150);
	~SpaceVehicles();
	static size_t SV_count;

    float speed;
	bool b_isInVehicle;
	bool b_vehDebounce;
	float rotationZ;
	int lap;
	bool lapDebounce;

    void updateVehicle(double deltaTime);
	void updateVehicle(double deltaTime , PMAP map);

	void enterVehicleUpdate(Player& player);
	void updateCPUVehicle(double deltaTime, PMAP map, queue<int>& q);
private:

    float acceleration;
    float rotateAngle;
    int max_speed;
	

};
#endif