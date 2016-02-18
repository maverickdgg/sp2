#ifndef WEAPON_H
#define WEAPON_H
#include "GameObject.h"

typedef unsigned short smaller;

class Weapon : public GameObject
{
public:
    ~Weapon();
    static size_t W_count;
    int dmg = 1;
    smaller attackSpeed = 1;
    float durability = 1.f;
protected:
    Weapon();
    Weapon(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
};
#endif