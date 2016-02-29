#include "Material.h"

Component::Component(float r, float g, float b)
{
	Set(r, g, b);
}

void Component::Set(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Material::Material()
{
	kAmbient = Component(0.2, 0.2, 0.2);
	kDiffuse = Component(0.3f, 0.3f, 0.3f);
	kSpecular = Component(0.1f, 0.1f, 0.1f);
	setShininess(0.5);
}

Material::~Material()
{
}

void Material::setShininess(float shine)
{
	this->kShininess = shine;
}