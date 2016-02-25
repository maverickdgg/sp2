#include "SpaceVehicles.h"

size_t SpaceVehicles::SV_count = 0;

SpaceVehicles::SpaceVehicles() : max_speed(25)
{
	SV_count++;
	b_vehDebounce = false;
	b_isInVehicle = false;
}

SpaceVehicles::SpaceVehicles(string object_name, int boundary, float viewAngle, Vector3 pos) : GameObject(object_name, boundary, viewAngle, pos), acceleration(50), speed(0), max_speed(250), rotateAngle(30)
{
	b_vehDebounce = false;
	b_isInVehicle = false;
}

SpaceVehicles::~SpaceVehicles()
{
	SV_count--;
}

void SpaceVehicles::updateVehicle(bool isPressedW ,bool isPressedS, bool isPressedA, bool isPressedD, double deltaTime)
{
    if (isPressedW == true && isPressedS == false)
    {
        if (speed < max_speed)
        {
            speed += acceleration ;
        }
    }

    if (isPressedS == true && isPressedW == false)
    {
        if (speed > -max_speed)
        {
            speed -= acceleration ;
        }
    }
    else if (isPressedW == false && isPressedS == false)
    {
        if (speed > 0)
        speed -= acceleration;
		if (speed < 0)
		{
			speed += acceleration;
		}
    }
   
    if (isPressedA == true && isPressedD == false)
    {
        viewAngle += rotateAngle * deltaTime;
    }
    if (isPressedD == true && isPressedA == false)
    {
        viewAngle -= rotateAngle * deltaTime;
    }
        pos.x += sin(Math::DegreeToRadian(viewAngle)) * speed * deltaTime;
        pos.z += cos(Math::DegreeToRadian(viewAngle)) * speed * deltaTime;
}

void SpaceVehicles::enterVehicleUpdate(Player& player)
{
	if (Application::IsKeyPressed('E') && b_vehDebounce == false && b_isInVehicle ==false && collision(player,this->pos,this->boundary + player.boundary + 10))
	{
		b_isInVehicle = true;
		b_vehDebounce = true;
	}
	else if (Application::IsKeyPressed('E') && b_vehDebounce == false && b_isInVehicle == true)
	{
		b_isInVehicle = false;
		b_vehDebounce = true;
		player.pos = this->pos;
	}
	if (!Application::IsKeyPressed('E') && b_vehDebounce == true)
	{
		b_vehDebounce = false;
	}
}