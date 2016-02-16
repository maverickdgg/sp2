#include "Alien.h"

size_t Alien::alien_count = 0;

Alien::Alien(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name,boundary,viewAngle,pos )
{
	++alien_count;
}

Alien::~Alien()
{
	--alien_count;
}