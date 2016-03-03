/******************************************************************************/
/*!
\file Buildings.cpp
\author Tan Hou Gim Samuel
\par email: 153942B@mymail.nyp.edu.sg
\brief Class for structural game objects, inherits from GameChar instead of GameObject
*/
/******************************************************************************/

#include "Buildings.h"

size_t Buildings::b_count = 0;

/******************************************************************************/
/*!
\brief
Default constructor that has a count which increments everytime a building object is declared
*/
/******************************************************************************/

Buildings::Buildings()
{
	b_count++;
}

/******************************************************************************/
/*!
\brief
Overloaded constructor that delegates variables such as name and position to GameChar constructor and increments count everytime an object is initialised
\param object_name
    String type variable to store name of structure
\param boundary
    Int type var to detect collision distance of player from object
\param viewAngle
    Float type var to store angle of rotation of object
\param pos
    Vector3 type var to store x-y-z position of object
*/
/******************************************************************************/

Buildings::Buildings(string object_name, int boundary, float viewAngle, Vector3 pos) : GameChar(object_name, boundary, viewAngle, pos)
{
	b_count++;
}

/******************************************************************************/
/*!
\brief
Default destructor
*/
/******************************************************************************/

Buildings::~Buildings()
{
	b_count--;
}

/******************************************************************************/
/*!
\brief
Function for logic in climbing the ladders
\param isClimb
    Bool to decide whether collision between player and ladder is true
\param ladder
    Class type var for user to pass in Building object
\param player
    Class type var for user to pass in Player object
*/
/******************************************************************************/

void Buildings::climb(bool& isClimb, Buildings& ladder, Player& player)
{
	if (collision(ladder.pos, player.pos, 20) == true)
	{
		isClimb = true;
	}
	else
		isClimb = false;
}