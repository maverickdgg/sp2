#ifndef BUILDINGS_H
#define BUILDINGS_H
#include "GameObject.h"
#include <vector>
using std::vector;

class Buildings : public GameObject
{
public:
	Buildings(string object_name, float viewAngle = 0, float positionX = 0, float positionY = 0);
	~Buildings();
	static size_t b_count;
	vector<GameObject> allOBJS;
};

#endif