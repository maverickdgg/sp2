#include "Player.h"
#include <sstream>
#include <iostream>
#include <iomanip>

vector<Quest*> Player::questList;

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

Player::~Player()
{
}


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

	cam.position = this->pos;
	cam.updateRotation(0.3);
}

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

bool Player::receiveQuest(GameChar& x)
{
	return receiveQuest(x.quest);
}

void Player::taskComplete(int questIIndex, int index)
{
	questList[questIIndex]->taskComplete(index);
}

bool Player::questCompleted(int index)
{
	if (questList[index]->questComplete() == true)
	{
		return true;
	}
	return false;
}

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

string Player::getOxygenString()
{
	string replace;
	replace.push_back((oxygen / 1000) + '0');

	replace.push_back(((oxygen / 100) % 10) + '0');
	replace.push_back('.');
	replace.push_back(((oxygen / 10) % 10) + '0');

	replace.push_back((oxygen % 10) + '0');
	//= std::to_string(oxygen);
	//if (oxygen / 100 != 0)
	//{
	//	replace = (oxygen / 100) + '0';
	//	replace += ((oxygen / 10) % 10) + '0';
	//	replace += (oxygen % 10) + '0';
	//}
	//else if (oxygen / 100 == 0 && oxygen / 10 != 0)
	//{
	//	replace = (oxygen / 10) + '0';
	//	replace += (oxygen % 10) + '0';
	//}
	//else
	//	replace = oxygen + '0'; 

	if (oxygen <= 0)
		replace = '0';
 
	return replace;
}