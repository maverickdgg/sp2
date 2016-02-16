#ifndef ALIEN_H
#define ALIEN_H
#include "GameChar.h"

class Alien : public GameChar
{
public:
    Alien(string object_name, float viewAngle = 0, float positionX = 0, float positionY = 0);
    ~Alien();
    static size_t count;
};

#endif