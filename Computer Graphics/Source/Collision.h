#ifndef COLLISION_H
#define COLLISION_H

#include "GameObject.h"
#include <vector>

using std::vector;

bool collision(GameObject x, GameObject y);
bool collision(GameObject x, vector<GameObject> y);
bool collision(GameObject x, Vector3 y, int boundary);
bool collision(Vector3 x, Vector3 y, int boundary);
vector<GameObject> collisionElimination(GameObject x, vector<GameObject> y);

#endif