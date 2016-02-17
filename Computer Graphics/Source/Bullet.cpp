#include "Bullet.h"

size_t Bullet::bullet_count = 0;

Bullet::Bullet(int boundary, float viewAngle, Vector3 pos) : GameObject("bullet", boundary, viewAngle, pos)
{
    ++bullet_count;
}

Bullet::~Bullet()
{
    --bullet_count;
}