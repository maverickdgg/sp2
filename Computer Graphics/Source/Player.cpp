#include "Player.h"

Player::Player()
{
	pos = Vector3(0, 0, 0);
	viewAngle = 0;
	boundary = 15;
	name = "Player";
	currGun = nullptr;
	f_walkSpeed = 70;
	f_sprintSpeed = 200;
	f_beforeJump = 0;
	b_jumpDebounce = false;
	b_jumpUp = true;
	f_jumpSpeed = 50;
	f_gravity = 25;
	f_initialJumpSpeed = 50;
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

void Player::movementUpdate(Camera3& cam , double dt)
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
	if (Application::IsKeyPressed('W') && !Application::IsKeyPressed('S'))
	{
		pos.x += cos(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
		pos.z -= sin(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
	}
	if (Application::IsKeyPressed('S') && !Application::IsKeyPressed('W'))
	{
		pos.x -= cos(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
		pos.z += sin(Math::DegreeToRadian(viewAngle)) * movSpeed * dt;
	}
	if (Application::IsKeyPressed('D') && !Application::IsKeyPressed('A'))
	{
		pos.x += sin(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
		pos.z += cos(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
	}
	if (Application::IsKeyPressed('A') && !Application::IsKeyPressed('D'))
	{
		pos.x -= sin(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
		pos.z -= cos(Math::DegreeToRadian(viewAngle)) * f_walkSpeed * dt;
	}
	if (Application::IsKeyPressed(VK_SPACE) && b_jumpDebounce == false)
	{
		f_beforeJump = pos.y;
		b_jumpDebounce = true;
		b_jumpUp = true;
		f_jumpSpeed = f_initialJumpSpeed;
	}
	if (b_jumpUp == true && b_jumpDebounce == true)
	{
		f_jumpSpeed -= f_gravity * dt;
		pos.y += f_jumpSpeed * dt;
		if (f_jumpSpeed <= 0)
		{
			f_jumpSpeed = 0;
			b_jumpUp = false;
		}
	}
	if (b_jumpUp == false && b_jumpDebounce == true)
	{
		f_jumpSpeed += f_gravity * dt;
		pos.y -= f_jumpSpeed * dt;
		if (f_jumpSpeed >= f_initialJumpSpeed)
		{
			f_jumpSpeed = f_initialJumpSpeed;
			b_jumpUp = true;
			b_jumpDebounce = false;
			pos.y = f_beforeJump;
		}
	}

	cam.position = this->pos;
	cam.updateRotation(0.3);
}