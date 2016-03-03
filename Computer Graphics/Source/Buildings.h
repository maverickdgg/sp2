/******************************************************************************/
/*!
\file Buildings.h
\author Tan Hou Gim Samuel
\par email: 153942B@mymail.nyp.edu.sg
\brief Class for structural game objects, inherits from GameChar instead of GameObject
*/
/******************************************************************************/

#ifndef BUILDINGS_H
#define BUILDINGS_H
#include "GameChar.h"
#include "Player.h"

class Buildings : public GameChar
{
public:
	Buildings();
	Buildings(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
	~Buildings();
	static size_t b_count;
	vector<GameObject> allOBJS;
	void climb(bool& isClimb, Buildings& ladder, Player& player);
};
#endif