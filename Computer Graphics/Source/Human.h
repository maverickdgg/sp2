#ifndef HUMAN_H
#define HUMAN_H
#include "GameChar.h"

class Human : public GameChar
{
public:
    Human(string object_name, float viewAngle = 0, float positionX = 0, float positionY = 0);
    ~Human();
    static size_t count;
};

#endif