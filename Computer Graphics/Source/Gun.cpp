#include "Gun.h"

size_t Gun::G_count = 0;

Gun::Gun() : totalAmmo(100), currAmmo(30), magCap(30), maxAmmo(200)
{
	this->pos = Vector3(0, 0, 0);
	G_count++;
}

Gun::Gun(string name, int boundary, Vector3 pos) : Weapon(name, boundary, 0, pos), totalAmmo(100), currAmmo(30), magCap(30), maxAmmo(200)
{
	this->pos = pos;
	fireRate = 1;
	fireDebounceTimer = 1/fireRate;
}

Gun::~Gun()
{
	G_count--;
}

void Gun::fire( double dt)
{
	if (fireDebounceTimer == 0)
	{
		bulletVec.push_back(Bullet(5, this->pos + this->view * 15 + Vector3(0, 1, 0), this->view, viewAngle, viewAngleX));
		fireDebounceTimer = 1 / fireRate;
	}
}

vector<Bullet>::iterator Gun::despawnBullet(vector<Bullet>::iterator it)
{
	return bulletVec.erase(it);
}

void Gun::updateBullet(double dt)
{
	fireDebounceTimer -= dt;
	if (fireDebounceTimer < 0)
	{
		fireDebounceTimer = 0;
	}
	for (vector<Bullet>::iterator it = bulletVec.begin(); it != bulletVec.end();)
	{
		it->bulletUpdate(dt);
		
		if (it->despawnTimer <= 0)
		{
			it = despawnBullet(it);
		}
		else 
		{
			it++;
		}
	}
}

float Gun::findAngle(Vector3 view)
{
    view = Vector3(view.x, 0, view.z);
    if (view.z >=0)
        viewAngle = Math::RadianToDegree(atan(view.x / view.z))-90 ;
    else
        viewAngle = Math::RadianToDegree(atan(view.x/view.z)) - 180 -90;
    return viewAngle;
}


