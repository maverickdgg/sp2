#include "GameChar.h"

size_t GameChar::count = 0;

GameChar::GameChar(string name, float viewAngle, float posX, float posY) : GameObject(name, viewAngle, posX, posY)
{
    count = 0;
}

GameChar::~GameChar()
{

}