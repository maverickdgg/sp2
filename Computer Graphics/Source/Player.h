/******************************************************************************/
/*!
\file	Player.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define the player for the game while inheriting from GameChar
*/
/******************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include "GameChar.h"
#include "Application.h"
#include "Camera3.h"
#include "Quest.h"
#include "Collision.h"
#include "Map.h"

#include <vector>

using std::vector;
/******************************************************************************/
/*!
Class Player:
\brief
Class for Player (Inheriting from GameChar)
/******************************************************************************/
class Player : public GameChar
{
public:

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

	static vector<Quest*> questList;

	void movementUpdate(Camera3& cam, double dt, vector<GameObject*> collisionVec);
	void movementUpdate(Camera3& cam, double dt, vector<GameObject*> collisionVec,PMAP map);
	bool haveAcceptedCheck(Quest* q);
	bool receiveQuest(Quest* q);
	bool receiveQuest(GameChar& x);
	void taskComplete(int questIndex, int index);
	bool questCompleted(int index);
	void setQuest();
	bool completedMainQuest();
	string getOxygenString();
};
#endif