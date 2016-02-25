#include "AlienEnemy.h"

size_t AlienEnemy::alienEnemy_count = 0;

AlienEnemy::AlienEnemy()
{
	alienEnemy_count++;
}

AlienEnemy::AlienEnemy(string object_name, int boundary, float viewAngle, Vector3 pos) : Alien(object_name, boundary, viewAngle, pos)
{
	alienEnemy_count++;
}

AlienEnemy::~AlienEnemy()
{
	alienEnemy_count--;
}