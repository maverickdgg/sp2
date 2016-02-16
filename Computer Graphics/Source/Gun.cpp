#include "Gun.h"

size_t Gun::G_count = 0;

Gun::Gun(string name, float viewAngle, float posX, float posY) : Weapon(name, viewAngle, posX, posY)
{
    ++G_count;
}

Gun::~Gun()
{
    --G_count;
}