/******************************************************************************/
/*!
\file	Material.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Structs for material
*/
/******************************************************************************/
#ifndef _MATERIAL_H
#define _MATERIAL_H
/******************************************************************************/
/*!
Struct Component:
\brief
Struct for component
/******************************************************************************/
struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f);

	void Set(float r, float g, float b);

};
/******************************************************************************/
/*!
Struct Material
\brief
Struct for material
/******************************************************************************/
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;

	void setShininess(float shine);

	Material();
	~Material();
};
#endif