#include "Player.h"

Player::Player()
{
	pos = Vector3(0, 0, 0);
	viewAngle = 0;
	boundary = 15;
	name = "Player";
	currGun = nullptr;
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

