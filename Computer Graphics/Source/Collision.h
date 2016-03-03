/******************************************************************************/
/*!
\file	Collision.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define the overall collision for the scenes
*/
/******************************************************************************/
#ifndef COLLISION_H
#define COLLISION_H

#include "GameObject.h"

bool collision(GameObject x, GameObject y);
bool collision(GameObject x, vector<GameObject> y);
bool collision(GameObject x, Vector3 y, int boundary);
bool collision(Vector3 x, Vector3 y, int boundary);
bool collision(Vector3 x, vector<GameObject*> y, float boundary);
bool collisionXZ(Vector3 x,GameObject y);
vector<GameObject> collisionElimination(GameObject x, vector<GameObject> y);

#endif