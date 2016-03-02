#ifndef ALIENENEMY_H
#define ALIENENEMY_H
#include "Alien.h"

/******************************************************************************/
/*!
Class AlienEnemy:
\brief	Providing the AlienEnemies to move ( inherits from Alien )
/******************************************************************************/

class AlienEnemy : public Alien
{
	bool isTurned;
	float turnSpeed;
public:
	AlienEnemy();
	AlienEnemy(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~AlienEnemy();
	void translateWorm(double dt);
	void move(double dt);
	float wormtranslating;
	float wormrotating;
	float wormtranslate;
	float wormrotate;

	float necroTranslating;
	float necroRotating;
	float necroTranslate;
	float necroRotate;
};

#endif