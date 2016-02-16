#include "GameObject.h"

size_t GameObject::count = 0;

GameObject::GameObject()
{
}

GameObject::GameObject(string object_name,int boundary, float viewAngle, Vector3 pos)
{
	this->boundary = boundary;
	this->name = object_name;
	this->pos = pos;
	
}

GameObject::~GameObject()
{
	
}