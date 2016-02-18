#ifndef GAME_CHAR_H
#define GAME_CHAR_H

#include "GameObject.h"

class GameChar : public GameObject
{
public:
	GameChar();
	GameChar(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));
    ~GameChar();
    static size_t GC_count;
	vector<string> vec_dialog;
	vector<string> ReadFromTxt(string link);
};

#endif