#ifndef BB_8_H
#define BB_8_H

#include "GameChar.h"

class BB8 :public GameChar
{
public:
	BB8();
	BB8(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~BB8();
	static size_t bb8_count;


};
#endif