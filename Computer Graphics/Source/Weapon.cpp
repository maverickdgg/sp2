#include "Weapon.h"

size_t Weapon::W_count = 0;

Weapon::Weapon()
{
	++W_count;
}

Weapon::Weapon(string name, int boundary, float viewAngle, Vector3 pos) : GameObject(name, boundary, viewAngle, pos)
{
	++W_count;
}

Weapon::~Weapon()
{
	--W_count;
}