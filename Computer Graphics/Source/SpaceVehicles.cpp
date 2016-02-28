#include "SpaceVehicles.h"

size_t SpaceVehicles::SV_count = 0;

SpaceVehicles::SpaceVehicles() : max_speed(25)
{
	SV_count++;
	b_vehDebounce = false;
	b_isInVehicle = false;
}

SpaceVehicles::SpaceVehicles(string object_name, int boundary, float viewAngle, Vector3 pos) : GameObject(object_name, boundary, viewAngle, pos), acceleration(25), speed(0), max_speed(100), rotateAngle(50)
{
	b_vehDebounce = false;
	b_isInVehicle = false;
	rotationZ = 0;
}

SpaceVehicles::~SpaceVehicles()
{
	SV_count--;
}

void SpaceVehicles::updateVehicle(double deltaTime)
{
	if (Application::IsKeyPressed('W') && !Application::IsKeyPressed('S'))
    {
        if (speed < max_speed)
        {
            speed += acceleration * deltaTime;
        }
		if (speed>max_speed)
		{
			speed = max_speed;
		}
    }

	if (Application::IsKeyPressed('S') && !Application::IsKeyPressed('W'))
    {
        if (speed > -max_speed)
        {
            speed -= acceleration * deltaTime;
        }
		if (speed < -max_speed)
		{
			speed = -max_speed;
		}
    }
	else if (!Application::IsKeyPressed('W') && !Application::IsKeyPressed('S'))
    {
        if (speed > 0)
        speed -= acceleration * deltaTime;
		if (speed < 0)
		{
			speed += acceleration * deltaTime;
		}
    }
   
	if (Application::IsKeyPressed('A') && !Application::IsKeyPressed('D'))
    {
		if (rotationZ <= 0)
		{
			viewAngle += rotateAngle * deltaTime;
		}
        
		if (rotationZ > -45)
			rotationZ -= rotateAngle* deltaTime;
		else if (rotationZ < -45)
			rotationZ = -45;
    }
	if (Application::IsKeyPressed('D') && !Application::IsKeyPressed('A'))
    {
		if (rotationZ >= 0)
		{
			viewAngle -= rotateAngle * deltaTime;
		}
		if (rotationZ < 45)
			rotationZ += rotateAngle* deltaTime;
		else if (rotationZ > 45)
			rotationZ = 45;
    }
	if (!Application::IsKeyPressed('A') && !Application::IsKeyPressed('D'))
	{
		if (rotationZ > 0)
		{
			rotationZ -= rotateAngle* deltaTime;
		}
		if (rotationZ < 0)
		{
			rotationZ += rotateAngle* deltaTime;
		}
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