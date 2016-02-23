#ifndef BUILDINGS_H
#define BUILDINGS_H
#include "GameChar.h"

class Buildings : public GameChar
{
public:
	Buildings();
	Buildings(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Buildings();
	static size_t b_count;
	vector<GameObject> allOBJS;
};
#endif