#include "AlienEnemy.h"

AlienEnemy::AlienEnemy()
{

}

AlienEnemy::AlienEnemy(string object_name, int boundary, float viewAngle, Vector3 pos) : Alien(object_name, boundary, viewAngle, pos)
{
    turnSpeed = 45;
    isTurned = false;
}

AlienEnemy::~AlienEnemy()
{

}

void AlienEnemy::translateWorm(double dt)
{
    if (isTurned == false)
    {
        viewAngle += turnSpeed*dt;
        if (viewAngle > 10)
        {
            isTurned = true;
        }
    }
    else if (isTurned == true)
    {
        viewAngle -= turnSpeed*dt;
        if (viewAngle < -10)
        {
            isTurned = false;
        }
    }
}