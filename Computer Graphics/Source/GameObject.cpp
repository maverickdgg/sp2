/******************************************************************************/
/*!
\file GameObject.cpp
\author Daniel
\brief GameObject class
*/
/******************************************************************************/

#include "GameObject.h"

size_t GameObject::GO_count = 0;

/******************************************************************************/
/*!
\brief
Default constructor that has a count which increments everytime a game object is declared or any object since they all inherit from this class
*/
/******************************************************************************/

GameObject::GameObject()
{
	GO_count++;
}

/******************************************************************************/
/*!
\brief
Overloaded constructor that with properties such as name, boundary and position and increments count everytime an object is initialised
\param object_name
String type variable to store name of object
\param boundary
Int type var to detect collision distance of player from object
\param viewAngle
Float type var to store angle of rotation of object
\param pos
Vector3 type var to store x-y-z position of object
*/
/******************************************************************************/

GameObject::GameObject(string object_name, int boundary, float viewAngle, Vector3 pos)
{
	this->boundary = boundary;
	this->name = object_name;
	this->pos = pos;
	this->viewAngle = viewAngle;
}

/******************************************************************************/
/*!
\brief
Default destructor that decrements the count of objects in the scene if they are deleted or unintialised
*/
/******************************************************************************/

GameObject::~GameObject()
{
	GO_count--;
}