#include "BB-8.h"

size_t BB8::bb8_count = 0;

BB8::BB8()
{
	bb8_count++;
}

BB8::BB8(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	bb8_count++;
}

BB8::~BB8()
{
	bb8_count--;
}