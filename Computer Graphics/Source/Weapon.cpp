#include "Weapon.h"

size_t Weapon::W_count = 0;

Weapon::Weapon(string name, float viewAngle, float posX, float posY) : GameObject(name, viewAngle, posX, posY)
{
    ++W_count;
}

Weapon::~Weapon()
{
    --W_count;
}