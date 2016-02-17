#ifndef BULLET_H
#define BULLET_H
#include "GameObject.h"

class Bullet : public GameObject
{
public:
    Bullet(int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
    ~Bullet();
    static size_t bullet_count;
    float viewAngle = 0;
};

#endif