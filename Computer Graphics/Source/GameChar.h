#ifndef GAME_CHAR_H
#define GAME_CHAR_H

#include "GameObject.h"
#include "Application.h"
#include "Collision.h"
#include "Quest.h"

class GameChar : public GameObject
{
protected:
	GameChar();
	GameChar(string object_name, int boundary, float viewAngle = 0, Vector3 pos = Vector3(0, 0, 0));

public:
    ~GameChar();
    static size_t GC_count;
	int dialogue_index;
	bool b_indexDebounce;
	bool isPressed;
	vector<string> vec_dialog;
	vector<string> ReadFromTxt(string link);
	void chat_update(Vector3 player_pos);
	int chat_boundary;

	Quest* quest;

	void assignQuest(Quest* q);
};
#endif