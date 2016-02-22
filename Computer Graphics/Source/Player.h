#ifndef PLAYER_H
#define PLAYER_H

#include "GameChar.h"
#include "Gun.h"

class Player : public GameChar
{
public:
	Gun* currGun;

	Player();
	~Player();

	void assignGun(Gun* newGun);
};
#endif