#include "GameChar.h"

size_t GameChar::count = 0;

GameChar::GameChar(string object_name, int boundary, float viewAngle, Vector3 pos) : GameObject(object_name, boundary, viewAngle, pos)
{
    count = 0;
}

GameChar::~GameChar()
{

}