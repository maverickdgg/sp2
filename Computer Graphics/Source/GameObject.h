#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <string>
#include "Vector3.h"

using std::string;

class GameObject
{
private:
    string name;
    static size_t GO_count;
	int boundary;
	Vector3 pos;
public:
    virtual ~GameObject();
protected:
    GameObject();
	GameObject(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));

};

#endif
