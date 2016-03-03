
/******************************************************************************/
/*!
\file	Vertex.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Structs to define the different types of vertex
*/
/******************************************************************************/
#ifndef _VERTEX_H
#define _VERTEX_H

#include "Vector3.h"
/******************************************************************************/
/*!
Struct Position:
\brief
Struct for the Position
/******************************************************************************/
struct Position
{
	float x, y, z;
	void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
	Position(float x = 0, float y = 0, float z = 0) { Set(x, y, z); }
	Position(Vector3 x){ this->Set(x.x, x.y, x.z); }

};


/******************************************************************************/
/*!
Struct Color:
\brief
Struct for the colors
/******************************************************************************/
struct Color
{
	float r, g, b;
	Color(float r = 1, float g = 1, float b = 1) { Set(r, g, b); }
	void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
	
};

/******************************************************************************/
/*!
Struct TexCoord
\brief
Struct for the coordinates
/******************************************************************************/
struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0)
	{
		Set(u, v);
	}

	void Set(float u, float v) { this->u = u; this->v = v; }
};


/******************************************************************************/
/*!
Struct Vertex:
\brief
Struct for Vertex indicating the position, colors, normal as well as the coordinates
/******************************************************************************/

struct Vertex
{
	Position pos;
	Color col;
	Vector3 normal;
	TexCoord texCoord;
};

#endif