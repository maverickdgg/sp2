#ifndef WEAPON_H
#define WEAPON_H
#include "GameObject.h"

class Weapon : public GameObject
{
public:
    Weapon(string object_name, float viewAngle = 0, float positionX = 0, float positionY = 0);
    ~Weapon();
    static size_t W_count;
    int dmg = 1;
    unsigned short attackSpeed = 1;
    float durability = 1.f;
};

#endif