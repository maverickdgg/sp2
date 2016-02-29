#ifndef SIR_H
#define SIR_H
#include "GameChar.h"

class Sir : public GameChar
{
	bool isTurned;
	float turnSpeed;
public:
	Sir();
	Sir(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Sir();
	void Salute(double dt);
};

#endif