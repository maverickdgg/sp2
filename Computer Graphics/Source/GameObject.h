#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <string>

using std::string;

class GameObject
{
private:
    string name;
    static size_t count;
public:
    virtual ~GameObject();
protected:
    GameObject();
    GameObject(string object_name, float viewAngle = 0, float positionX = 0, float positionY = 0);

};

#endif
