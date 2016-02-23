#ifndef PLAYER_H
#define PLAYER_H

#include "GameChar.h"
#include "Gun.h"
#include "Application.h"
#include "Camera3.h"
#include "Quest.h"

#include <vector>

using std::vector;

class Player : public GameChar
{
public:
	Gun* currGun;

	Player();
	~Player();

	float f_walkSpeed;
	float f_sprintSpeed;
	float f_beforeJump;
	float f_initialJumpSpeed;
	float f_jumpSpeed;
	float f_gravity;
	bool b_jumpDebounce;
	bool b_jumpUp;

	vector<Quest*> questList;

	void assignGun(Gun* newGun);
	void movementUpdate(Camera3& cam, double dt);
	void gunUpdate(Camera3 cam, double dt);
	bool receiveQuest(Quest* q);
	bool receiveQuest(GameChar& x);
	bool questCompleted(Quest* q);
};
#endif