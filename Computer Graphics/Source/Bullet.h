#ifndef BULLET_H
#define BULLET_H
#include "GameObject.h"

class Bullet
{
public:
	int boundary;
	float angleY;
	float angleX;
	float despawnTimer;
	Vector3 view;
	Vector3 pos;

	Bullet(int boundary, Vector3 pos = Vector3(0, 0, 0),Vector3 view = Vector3(0,0,0) ,float angleY = 0, float angleX = 0);
    ~Bullet();
	void bulletUpdate(float dt);
    static size_t bullet_count;
};
#endif