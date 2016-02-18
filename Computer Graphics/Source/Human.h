#ifndef HUMAN_H
#define HUMAN_H
#include "GameChar.h"

class Human : public GameChar
{
public:
	Human();
	Human(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
    ~Human();
    static size_t human_count;
};

#endif