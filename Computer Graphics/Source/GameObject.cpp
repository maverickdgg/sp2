#include "GameObject.h"

size_t GameObject::GO_count = 0;
vector<GameObject*> GameObject::allGameObj;

GameObject::GameObject()
{
	//allGameObj.push_back(*this);
	GO_count++;
}

GameObject::GameObject(string object_name, int boundary, float viewAngle, Vector3 pos)
{
	this->boundary = boundary;
	this->name = object_name;
	this->pos = pos;
    this->viewAngle = viewAngle;
	GO_count++;
	allGameObj.push_back(this);
}

GameObject::~GameObject()
{
	GO_count--;
	//for (vector<GameObject*>::iterator it = allGameObj.begin(); it != allGameObj.end();)
	//{
	//	if (*it == this)
	//	{
	//		allGameObj.erase(it);
	//		break;
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}
}