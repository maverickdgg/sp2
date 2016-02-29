#ifndef _VERTEX_H
#define _VERTEX_H

#include "Vector3.h"

struct Position
{
	float x, y, z;
	void Set(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	Position(float x = 0, float y = 0, float z = 0)
	{
		Set(x, y, z);
	}

};

struct Color
{
	float r, g, b;
	void Set(float r, float g, float b)
	{
		this->r = r; this->g = g; this->b = b;
	}
	Color(float r = 0, float g = 0, float b = 0)
	{
		Set(r, g, b);
	}

};

struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0) { Set(u, v); }
	void Set(float u, float v) { this->u = u; this->v = v; }
};


struct Vertex
{
	Position pos;
	Color col;
	Vector3 normal;
	TexCoord texCoord;
};
#endif