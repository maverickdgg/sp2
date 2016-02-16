#ifndef GUN_H
#define GUN_H
#include "Weapon.h"

class Gun : public Weapon
{
public:
    Gun(string object_name, float viewAngle = 0, float positionX = 0, float positionY = 0);
    ~Gun();
    static size_t G_count;

};

#endif