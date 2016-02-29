#include "Alien.h"

size_t Alien::alien_count = 0;

Alien::Alien()
{
	alien_count++;
}

Alien::Alien(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	alien_count++;
	b_scaleUp = true;
	f_scaleBig = 0;
}

Alien::~Alien()
{
	alien_count--;
}

void Alien::pulsingUpdate(double dt)
{
	if (b_scaleUp == true)
	{
		f_scaleBig += dt;
	}
	else
	{
		f_scaleBig -= dt;
		if (f_scaleBig < 0)
		{
			f_scaleBig = 0;
		}
	}
	if (f_scaleBig >3)
	{
		b_scaleUp = false;
	}
	else if (f_scaleBig <= 0)
	{
		b_scaleUp = true;
	}
}