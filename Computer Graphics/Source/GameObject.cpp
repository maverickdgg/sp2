#include "GameObject.h"

size_t GameObject::GO_count = 0;

GameObject::GameObject()
{
	GO_count++;
}

GameObject::GameObject(string object_name, int boundary, float viewAngle, Vector3 pos)
{
	this->boundary = boundary;
	this->name = object_name;
	this->pos = pos;
    this->viewAngle = viewAngle;
	GO_count++;
}

GameObject::~GameObject()
{
	GO_count--;
}