#include "SpaceVehicles.h"

size_t SpaceVehicles::SV_count = 0;

SpaceVehicles::SpaceVehicles() : max_speed(25)
{
	SV_count++;
}

SpaceVehicles::SpaceVehicles(string object_name, int boundary, float viewAngle, Vector3 pos) : GameObject(object_name, boundary, viewAngle, pos), acceleration(10), speed(0), max_speed(100), rotateAngle(30)
{
}

SpaceVehicles::~SpaceVehicles()
{
	SV_count--;
}

void SpaceVehicles::updateVehicle(bool isPressedW ,bool isPressedS, bool isPressedA, bool isPressedD, float deltaTime)
{
    if (isPressedW == true && isPressedS == false)
    {
        if (speed < max_speed)
        {
            speed += acceleration;
        }
    }

    if (isPressedS == true && isPressedW == false)
    {
        if (speed > -max_speed)
        {
            speed -= acceleration;
        }
    }
    else if (isPressedW == false && isPressedS == false)
    {
        if (speed > 0)
        speed -= acceleration;
        else if (speed < 0)
        {
            if (speed != 0)
                ++speed;
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
        pos.x -= sin(Math::DegreeToRadian(viewAngle)) * speed * deltaTime;
        pos.z -= cos(Math::DegreeToRadian(viewAngle)) * speed * deltaTime;
}
