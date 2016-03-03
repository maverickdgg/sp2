/******************************************************************************/
/*!
\file	SpaceVehicles.h
\author Daniel Chua
\par	Email: 152112Y\@mymail.nyp.edu.sg
\par	Admin Number: 152112Y
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9025 8239
\brief
Class to define Space Vehicles
*/
/******************************************************************************/
#ifndef SPACE_VEHICLES_H
#define SPACE_VEHICLES_H
#include "GameObject.h"
#include "Application.h"
#include "Player.h"
#include "Map.h"

#include <queue>

using std::queue;
/******************************************************************************/
/*!
Class SpaceVehicles:
\brief
Class for Space Vehicles inheriting from GameObject
/******************************************************************************/
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
	int max_speed;
	queue<int> racepath;

    void updateVehicle(double deltaTime);
	void updateVehicle(double deltaTime , PMAP map,queue<int>& q);
	void updateVehicle2(double deltaTime, PMAP map, queue<int>& q);

	void enterVehicleUpdate(Player& player);
	void updateCPUVehicle(double deltaTime, PMAP map, queue<int>& q);
	
	int getRacePosition(SpaceVehicles x, int startIndex);
	int positionInQueue(int index);
	float distanceFromCheckpoint();
private:

    float acceleration;
    float rotateAngle;
    
	

};
#endif