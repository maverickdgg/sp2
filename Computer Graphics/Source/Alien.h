#ifndef ALIEN_H
#define ALIEN_H
#include "GameChar.h"

class Alien : public GameChar
{
public:
    Alien(string object_name, int boundary, float viewAngle, Vector3 pos);
    ~Alien();
    static size_t alien_count;
};

#endif