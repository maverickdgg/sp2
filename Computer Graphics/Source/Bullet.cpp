#include "Bullet.h"

size_t Bullet::bullet_count = 0;

Bullet::Bullet(int boundary, Vector3 pos, Vector3 view, float angleY, float angleX) :boundary(boundary), pos(pos), angleY(angleY), angleX(angleX), despawnTimer(3), view(view)
{
    ++bullet_count;
}

Bullet::~Bullet()
{
    --bullet_count;
}

void Bullet::bulletUpdate(float dt)
{
	this->pos += this->view * 10;
	this->despawnTimer -= dt;
}