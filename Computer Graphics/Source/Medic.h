#ifndef MEDIC_H
#define MEDIC_H
#include "GameChar.h"

class Medic : public GameChar
{
public:
	Medic();
	Medic(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Medic();
	static size_t medic_count;
};
#endif