#include "Collision.h"

bool collision(GameObject x, GameObject y)
{
	Vector3 distance = x.pos + y.pos;
	float length = distance.Length();
	if (length > x.boundary + y.boundary)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool collision(GameObject x, vector<GameObject> y)
{
	for (vector<GameObject>::iterator it = y.begin(); it != y.end(); ++it)
	{
		if (collision(x, *it) == true)
		{
			return true;
		}
	}
	return false;
}

vector<GameObject> collisionElimination(GameObject x, vector<GameObject> y)
{
	vector<GameObject> result;
	for (vector<GameObject>::iterator it = y.begin(); it != y.end(); ++it)
	{
		if ((x.pos.y - it->pos.y < x.boundary + it->boundary) && (x.pos.y - it->pos.y > -(x.boundary + it->boundary)))
		{
			if (collision(x, *it) == true)
			{
				result.push_back(*it);
			}
		}
	}
	return result;
}