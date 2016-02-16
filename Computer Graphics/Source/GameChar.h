#ifndef GAME_CHAR_H
#define GAME_CHAR_H
#include "GameObject.h"

class GameChar : public GameObject
{
public:
    GameChar(string object_name, float viewAngle = 0, float positionX = 0, float positionY = 0);
    ~GameChar();
    static size_t count;
};

#endif