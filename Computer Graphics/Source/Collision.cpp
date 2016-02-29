#include "Collision.h"

bool collision(GameObject x, GameObject y)
{
	Vector3 distance = x.pos - y.pos;
	/*float length = distance.Length();
	if (length > x.boundary + y.boundary)
	{
	return false;
	}
	else
	{
	return true;
	}*/
	if (distance.x < 0)
	{
		distance.x *= -1;
	}
	if (distance.y < 0)
	{
		distance.y *= -1;
	}
	if (distance.z < 0)
	{
		distance.z *= -1;
	}
	if (distance.x < (x.boundary + y.boundary) && distance.y < (x.boundary + y.boundary) && distance.z < (x.boundary + y.boundary))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool collision(GameObject x, Vector3 y, int boundary)
{
	return collision(x.pos, y, (x.boundary + boundary));
}

bool collision(Vector3 x, Vector3 y, int boundary)
{
	Vector3 distance = x - y;

	if (distance.x < 0)
	{
		distance.x *= -1;
	}
	if (distance.y < 0)
	{
		distance.y *= -1;
	}
	if (distance.z < 0)
	{
		distance.z *= -1;
	}
	if (distance.x < (boundary) && distance.y < (boundary) && distance.z < (boundary))
	{
		return true;
	}
	else
	{
		return false;
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

bool collision(Vector3 x, vector<GameObject*> y, float boundary)
{
	for (vector<GameObject*>::iterator it = y.begin(); it != y.end(); ++it)
	{
		if ((*it)->pos != x)
		{
			if (collision(**it, x, boundary) == true)
			{
				return true;
			}
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