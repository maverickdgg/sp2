#ifndef _MATERIAL_H
#define _MATERIAL_H

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f);

	void Set(float r, float g, float b);

};

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