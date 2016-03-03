#include "Player.h"
#include <sstream>
#include <iostream>
#include <iomanip>

vector<Quest*> Player::questList;
/******************************************************************************/
/*!
\brief
default constructor for player. initialise default values for player
*/
/******************************************************************************/
Player::Player() : GameChar("Player", 15, 0, Vector3(0, 0, 0), 100)
{
	pos = Vector3(0, 0, 0);
	viewAngle = 0;
	boundary = 15;
	name = "Player";
	f_walkSpeed = 70;
	f_sprintSpeed = 200;
	b_jumpDebounce = false;
	b_jumpUp = true;
	f_jumpSpeed = 50;
	f_gravity = 50;
	f_initialJumpSpeed = 50;
	groundLevel = 0;
	f_jumpDebounceTimer = 0;
	oxygen = 100;
}

/******************************************************************************/
/*!
\brief
Overloaded constructor for player
\param pos
initial position of the player
*/
/******************************************************************************/
Player::Player(Vector3 pos)
{
	this->pos = pos;
	viewAngle = 0;
	boundary = 15;
	name = "Player";
	f_walkSpeed = 70;
	f_sprintSpeed = 200;
	b_jumpDebounce = false;
	b_jumpUp = true;
	f_jumpSpeed = 50;
	f_gravity = 50;
	f_initialJumpSpeed = 50;
	groundLevel = 0;
	f_jumpDebounceTimer = 0;
}
/******************************************************************************/
/*!
\brief
default destructor for player class
*/
/******************************************************************************/
Player::~Player()
{
}

/******************************************************************************/
/*!
\brief
player's movement update.Updates player position and camera.
\param cam
the camera that follows the player
\param dt
delta time
\param collisionVec
a vector of gameobject pointer used for collision detection
*/
/******************************************************************************/
void Player::movementUpdate(Camera3& cam, double dt, vector<GameObject*> collisionVec)
{
	float movSpeed;
	if (Application::IsKeyPressed(VK_SHIFT))
	{
		movSpeed = f_sprintSpeed;
	}
	else
	{
		movSpeed = f_walkSpeed;
	}
	Vector3 tempPos = pos;
	if (Application::IsKeyPressed('W') && !Application::IsKeyPressed('S'))
	{
		tempPos.x += cos(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
		tempPos.z -= sin(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
	}
	if (Application::IsKeyPressed('S') && !Application::IsKeyPressed('W'))
	{
		tempPos.x -= cos(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
		tempPos.z += sin(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
	}
	if (Application::IsKeyPressed('D') && !Application::IsKeyPressed('A'))
	{
		tempPos.x += sin(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
		tempPos.z += cos(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
	}
	if (Application::IsKeyPressed('A') && !Application::IsKeyPressed('D'))
	{
		tempPos.x -= sin(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
		tempPos.z -= cos(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
	}
	if (Application::IsKeyPressed(VK_SPACE) && b_jumpDebounce == false && f_jumpDebounceTimer >= 0.5)
	{
		f_jumpDebounceTimer = 0;
		b_jumpDebounce = true;
		b_jumpUp = true;
		f_jumpSpeed = f_initialJumpSpeed;
	}
	if (b_jumpUp == true && b_jumpDebounce == true)
	{
		f_jumpSpeed -= f_gravity * dt;
		tempPos.y += f_jumpSpeed * dt;
		if (f_jumpSpeed <= 0)
		{
			f_jumpSpeed = 0;
			b_jumpUp = false;
		}
		else if (collision(tempPos, collisionVec, this->boundary) == true)
		{
			b_jumpUp = false;
		}
		else {
			pos = tempPos;
		}
	}
	if (b_jumpUp == false && b_jumpDebounce == true)
	{
		f_jumpSpeed += f_gravity * dt;
		tempPos.y -= f_jumpSpeed * dt;
		if (tempPos.y <= groundLevel)
		{
			pos.y = groundLevel;
			f_jumpSpeed = f_initialJumpSpeed;
			b_jumpUp = true;
			b_jumpDebounce = false;
		}
		else if (collision(tempPos, collisionVec, this->boundary) == true)
		{
			f_jumpSpeed = f_initialJumpSpeed;
			b_jumpUp = true;
			b_jumpDebounce = false;
		}
		else
		{
			pos = tempPos;
		}
	}
	if (b_jumpDebounce == false && f_jumpDebounceTimer <0.5)
	{
		f_jumpDebounceTimer += dt;
	}

	if (pos.y > groundLevel && collision(pos - Vector3(0, 20, 0)*dt, collisionVec, this->boundary) == false && b_jumpDebounce == false)
	{
		pos.y -= 20 * dt;
	}
	else if (pos.y < groundLevel)
	{
		pos.y = groundLevel;
	}
	if (collision(tempPos, collisionVec, this->boundary) == false)
	{
		pos = tempPos;
	}
	if (pos.x > cam.boundaryX)
	{
		pos.x = cam.boundaryX;
	}
	else if (pos.x < -cam.boundaryX)
	{
		pos.x = -cam.boundaryX;
	}
	if (pos.z > cam.boundaryZ)
	{
		pos.z = cam.boundaryZ;
	}
	else if (pos.z < -cam.boundaryZ)
	{
		pos.z = -cam.boundaryZ;
	}

	cam.view = (cam.target - cam.position).Normalized();
	cam.right = cam.view.Cross(cam.defaultUp);
	cam.right.y = 0;
	cam.right.Normalize();
	cam.up = cam.right.Cross(cam.view).Normalized();

	cam.position = this->pos;
	cam.updateRotation(0.3);

	viewAngle = cam.cameraRotationY;
}
/******************************************************************************/
/*!
\brief
set the default quest of the player.
*/
/******************************************************************************/
void Player::setQuest()
{
	Quest* questPtr;
	vector<string> tasklist;
	tasklist.push_back("get first in space race");
	questPtr = new Quest(1,tasklist,"spaceRace");
	questList.push_back(questPtr);
	tasklist.clear();
	tasklist.push_back("get to the top platform");
	questPtr = new Quest(1, tasklist, "Platformer");
	questList.push_back(questPtr);
}

/******************************************************************************/
/*!
\brief
an overloaded movement update that for scenes with text generated map
\param cam
the camera that follows the player
\param dt
delta time
\param collisionVec
a vector of gameobject pointer used for collision detection
\param map
a pointer to a map that should be generated in thhe scene init(used for collision detection)
*/
/******************************************************************************/
void Player::movementUpdate(Camera3& cam, double dt, vector<GameObject*> collisionVec,PMAP map)
{
	float movSpeed;
	if (Application::IsKeyPressed(VK_SHIFT))
	{
		movSpeed = f_sprintSpeed;
	}
	else
	{
		movSpeed = f_walkSpeed;
	}
	cam.view = (cam.target - cam.position).Normalized();
	cam.right = cam.view.Cross(cam.defaultUp);
	cam.right.y = 0;
	cam.right.Normalize();
	cam.up = cam.right.Cross(cam.view).Normalized();

	viewAngle = cam.cameraRotationY;

	Vector3 tempPos = pos;
	if (Application::IsKeyPressed('W') && !Application::IsKeyPressed('S'))
	{
		tempPos.x += cos(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
		tempPos.z -= sin(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
	}
	if (Application::IsKeyPressed('S') && !Application::IsKeyPressed('W'))
	{
		tempPos.x -= cos(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
		tempPos.z += sin(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
	}
	if (Application::IsKeyPressed('D') && !Application::IsKeyPressed('A'))
	{
		tempPos.x += sin(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
		tempPos.z += cos(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
	}
	if (Application::IsKeyPressed('A') && !Application::IsKeyPressed('D'))
	{
		tempPos.x -= sin(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
		tempPos.z -= cos(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
	}
	
	if (Application::IsKeyPressed(VK_SPACE) && b_jumpDebounce == false && f_jumpDebounceTimer >= 0.5)
	{
		f_jumpDebounceTimer = 0;
		b_jumpDebounce = true;
		b_jumpUp = true;
		f_jumpSpeed = f_initialJumpSpeed;
	}
	if (b_jumpUp == true && b_jumpDebounce == true)
	{
		f_jumpSpeed -= f_gravity * dt;
		tempPos.y += f_jumpSpeed * dt;
		if (f_jumpSpeed <= 0)
		{
			f_jumpSpeed = 0;
			b_jumpUp = false;
		}
		else if (collision(tempPos, collisionVec, this->boundary) == true)
		{
			b_jumpUp = false;
		}
		if (collision(tempPos, collisionVec, this->boundary) == false && map->data[vectorToIndex(tempPos)] != '1')
		{
			pos = tempPos;
		}
		else
		{
			if (map->data[vectorToIndex(Vector3(tempPos.x, 0, pos.z))] != '1')
			{
				pos.x = tempPos.x;
			}
			else if (map->data[vectorToIndex(Vector3(pos.x, 0, tempPos.z))] != '1')
			{
				pos.z = tempPos.z;
			}
		}
	}
	if (b_jumpUp == false && b_jumpDebounce == true)
	{
		f_jumpSpeed += f_gravity * dt;
		tempPos.y -= f_jumpSpeed * dt;
		if (tempPos.y <= groundLevel)
		{
			pos.y = groundLevel;
			f_jumpSpeed = f_initialJumpSpeed;
			b_jumpUp = true;
			b_jumpDebounce = false;
		}
		else if (collision(tempPos, collisionVec, this->boundary) == true)
		{
			f_jumpSpeed = f_initialJumpSpeed;
			b_jumpUp = true;
			b_jumpDebounce = false;
		}
		if (collision(tempPos, collisionVec, this->boundary) == false && map->data[vectorToIndex(tempPos)] != '1')
		{
			pos = tempPos;
		}
		else
		{
			if (map->data[vectorToIndex(Vector3(tempPos.x, 0, pos.z))] != '1')
			{
				pos.x = tempPos.x;
			}
			else if (map->data[vectorToIndex(Vector3(pos.x, 0, tempPos.z))] != '1')
			{
				pos.z = tempPos.z;
			}
		}
	}
	if (b_jumpDebounce == false && f_jumpDebounceTimer <0.5)
	{
		f_jumpDebounceTimer += dt;
	}

	if (collision(tempPos, collisionVec, this->boundary) == false && map->data[vectorToIndex(tempPos)] != '1')
	{
		pos = tempPos;
	}
	else
	{
		if (map->data[vectorToIndex(Vector3(tempPos.x, 0, pos.z))] != '1')
		{
			pos.x = tempPos.x;
		}
		else if (map->data[vectorToIndex(Vector3(pos.x, 0, tempPos.z))] != '1')
		{
			pos.z = tempPos.z;
		}
	}
	if (pos.x > cam.boundaryX)
	{
		pos.x = cam.boundaryX;
	}
	else if (pos.x < -cam.boundaryX)
	{
		pos.x = -cam.boundaryX;
	}
	if (pos.z > cam.boundaryZ)
	{
		pos.z = cam.boundaryZ;
	}
	else if (pos.z < -cam.boundaryZ)
	{
		pos.z = -cam.boundaryZ;
	}

	if (pos.y > groundLevel && collision(pos - Vector3(0, 20, 0)*dt, collisionVec, this->boundary) == false && b_jumpDebounce == false)
	{
		pos.y -= 20 * dt;
	}
	else if (pos.y < groundLevel)
	{
		pos.y = groundLevel;
	}

	


	cam.position = this->pos;
	cam.updateRotation(0.3);
}


/******************************************************************************/
/*!
\brief
check if the quest is already in player's questlist.
\param q
quest pointer of the quest to check
\return
true if already inside questlist and false if it isn't
*/
/******************************************************************************/
bool Player::haveAcceptedCheck(Quest* q)
{
	for (vector<Quest*>::iterator it = questList.begin(); it != questList.end(); ++it)
	{
		if (*it == q)
		{
			return true;
		}
	}
	return false;
}

/******************************************************************************/
/*!
\brief
receive quest and insert into the player quest list
\param q
pointer to the quest to insert
\return
return true if quest is properly inserted , return false if not inserted.
*/
/******************************************************************************/

bool Player::receiveQuest(Quest* q)
{
	if (haveAcceptedCheck(q) == false)
	{
		for (vector<Quest*>::iterator it = questList.begin(); it != questList.end(); ++it)
		{
			if (*it == nullptr)
			{
				*it = q;
				return true;
			}
		}
	}
	return false;
}

/******************************************************************************/
/*!
\brief
overloaded receive quest that specify which npc player receive from
\param x
a game character that have a quest assigned to him
\return
return true if properly inserted and return false if it is not inserted.
*/
/******************************************************************************/

bool Player::receiveQuest(GameChar& x)
{
	return receiveQuest(x.quest);
}
/******************************************************************************/
/*!
\brief
completes the task 
\param questIIndex
index of the quest in the questlist vector
\param index
index of the task within the quest.
*/
/******************************************************************************/
void Player::taskComplete(int questIIndex, int index)
{
	questList[questIIndex]->taskComplete(index);
}

/******************************************************************************/
/*!
\brief
check if a quest in the questlist is completed
\param index
index of the quest within the questlist vector
\return 
true if quest is completed.
*/
/******************************************************************************/

bool Player::questCompleted(int index)
{
	if (questList[index]->questComplete() == true)
	{
		return true;
	}
	return false;
}
/******************************************************************************/
/*!
\brief
check if the main quest that are set under setQuest function is completed
\return
true if ALL the main quest are completed.
*/
/******************************************************************************/
bool Player::completedMainQuest()
{
	if (questCompleted(0) == true && questCompleted(1) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/******************************************************************************/
/*!
\brief
gets a string of the oxygen level
\return
string of oxygen level.
*/
/******************************************************************************/
string Player::getOxygenString()
{
	string replace;
	replace.push_back((oxygen / 1000) + '0');

	replace.push_back(((oxygen / 100) % 10) + '0');
	replace.push_back('.');
	replace.push_back(((oxygen / 10) % 10) + '0');

	replace.push_back((oxygen % 10) + '0');


	if (oxygen <= 0)
		replace = '0';
 
	return replace;
}