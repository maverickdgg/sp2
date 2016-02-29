#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <string>
#include <vector>
#include <fstream>
#include "MyMath.h"
#include "Vector3.h"
#include <algorithm>

using std::ifstream;
using std::ofstream;

using std::string;
using std::vector;

typedef unsigned short smaller;

using std::cout;
using std::endl;

class GameObject
{
private:

	static size_t GO_count;

public:
	string name;
	virtual ~GameObject();
	int boundary;
	Vector3 pos;
	float viewAngle;
protected:
	GameObject();
	GameObject(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));

};
#endif
