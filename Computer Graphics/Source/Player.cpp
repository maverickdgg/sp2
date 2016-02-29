#include "Player.h"

Player::Player() : GameChar("Player", 15, 0, Vector3(0, 0, 0), 100)
{
	pos = Vector3(0, 0, 0);
	viewAngle = 0;
	boundary = 15;
	name = "Player";
	currGun = nullptr;
	f_walkSpeed = 70;
	f_sprintSpeed = 200;
	b_jumpDebounce = false;
	b_jumpUp = true;
	f_jumpSpeed = 50;
	f_gravity = 50;
	f_initialJumpSpeed = 50;
	groundLevel = 0;
	f_jumpDebounceTimer = 0;

	for (int i = 0; i < 5; ++i)
	{
		questList.push_back(nullptr);
	}
}

Player::~Player()
{
}

void Player::assignGun(Gun* newGun)
{
	if (currGun == nullptr)
	{
		currGun = newGun;
	}
	else
	{
		delete currGun;
		currGun = newGun;
	}
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

	cam.position = this->pos;
	cam.updateRotation(0.3);
}

void Player::gunUpdate(Camera3 cam, double dt)
{
	if (currGun == nullptr)
	{
		return;
	}
	currGun->view = cam.view;
	currGun->viewAngleX = cam.cameraRotationX;
	currGun->viewAngle = cam.cameraRotationY;
	currGun->pos = Vector3(cam.position.x, cam.position.y - 5, cam.position.z);

	if (Application::IsKeyPressed(VK_LBUTTON) && currGun->currAmmo >0)
	{
		currGun->fire(dt);
	}
	currGun->updateBullet(dt);
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

bool Player::taskComplete(Quest* q, int index)
{
	if (index > q->numTasks || haveAcceptedCheck(q) == false)
	{
		return false;
	}
	else
	{
		for (vector<Quest*>::iterator it = questList.begin(); it != questList.end(); ++it)
		{
			if (*it == q)
			{
				(*it)->task[index] = true;
				questCompleted(q);
				return true;
			}
		}
	}
}

bool Player::questCompleted(Quest* q)
{
	if (q->questComplete() == true)
	{
		for (vector<Quest*>::iterator it = questList.begin(); it != questList.end(); ++it)
		{
			if (*it == q)
			{
				*it = nullptr;
				return true;
			}
		}
	}
	return false;
}