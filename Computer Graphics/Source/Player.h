#ifndef PLAYER_H
#define PLAYER_H

#include "GameChar.h"
#include "Gun.h"
#include "Application.h"
#include "Camera3.h"
#include "Quest.h"
#include "Collision.h"
#include "Map.h"

#include <vector>

using std::vector;

class Player : public GameChar
{
public:
	Gun* currGun;

	Player();
	Player(Vector3 pos);
	~Player();

	float f_walkSpeed;
	float f_sprintSpeed;
	float f_jumpDebounceTimer;
	float f_initialJumpSpeed;
	float f_jumpSpeed;
	float f_gravity;
	bool b_jumpDebounce;
	bool b_jumpUp;
	float groundLevel;
	smaller oxygen;

	vector<Quest*> questList;

	void assignGun(Gun* newGun);
	void movementUpdate(Camera3& cam, double dt, vector<GameObject*> collisionVec);
	void movementUpdate(Camera3& cam, double dt, vector<GameObject*> collisionVec,PMAP map);
	void gunUpdate(Camera3 cam, double dt);
	bool haveAcceptedCheck(Quest* q);
	bool receiveQuest(Quest* q);
	bool receiveQuest(GameChar& x);
	bool taskComplete(Quest* q, int index);
	bool questCompleted(Quest* q);
	string getOxygenString();
};
#endif