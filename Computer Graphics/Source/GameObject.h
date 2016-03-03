/******************************************************************************/
/*!
\file	GameObject.h
\author Daniel Chua
\par	Email: 152112Y\@mymail.nyp.edu.sg
\par	Admin Number: 152112Y
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9025 8239
\brief
Class to define GameObject
*/
/******************************************************************************/
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "MyMath.h"
#include "Vector3.h"

using std::ifstream;
using std::ofstream;

using std::string;
using std::vector;

typedef unsigned short smaller;

using std::cout;
using std::endl;
/******************************************************************************/
/*!
Class GameObject:
\brief
Class for GameObject
/******************************************************************************/
class GameObject
{
private:

	static size_t GO_count;

public:
	string name;
	virtual ~GameObject();
	int boundary;
	Vector3 pos;
	float viewAngle;
protected:
	GameObject();
	GameObject(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));

};
#endif
