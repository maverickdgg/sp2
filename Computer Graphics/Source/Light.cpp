#include "Light.h"

Light::Light()
{
	// default constructor
	position.Set(0, 0, 0);
	color.Set(1, 1, 1);
	power = 1.f;
	kC = kL = kQ = 0;
}

