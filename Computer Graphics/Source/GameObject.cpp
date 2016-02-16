#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(string object_name, float viewAngle, float positionX, float positionY)
{
    object_name = name;
    positionX = 0;
    positionY = 0;
}

GameObject::~GameObject()
{
}