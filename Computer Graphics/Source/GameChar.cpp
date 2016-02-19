#include "GameChar.h"
#include <iostream>

using std::cout;
using std::endl;

size_t GameChar::GC_count = 0;

GameChar::GameChar()
{
	chat_boundary = 100;
	GC_count++;
	b_indexDebounce = false;
	dialogue_index = 0;
}

GameChar::GameChar(string object_name, int boundary, float viewAngle, Vector3 pos) : GameObject(object_name, boundary, viewAngle, pos)
{
	chat_boundary = 100;
	++GC_count;
	dialogue_index = 0;
	b_indexDebounce = false;
}

GameChar::~GameChar()
{
	--GC_count;
}

vector<string> GameChar::ReadFromTxt(string link)
{
	ifstream inData;
	inData.open(link, std::ifstream::in);

	if (!inData)
	{
		cout << "Error Opening" << link << endl;
		exit(1);
	}
	if (inData.good())
	{
		while (inData.good())
		{
			string data;
			std::getline(inData, data);
			vec_dialog.push_back(data);
		}
	}
	{inData.close();
	return vec_dialog;
	}
}

void GameChar::chat_update(Vector3 player_pos)
{
	// NPC Text Indexing
	if (Application::IsKeyPressed('E') && b_indexDebounce == false && collision(player_pos, pos, chat_boundary) == true)
	{
		if (isPressed == true)
		{
		++dialogue_index;
		if (dialogue_index >= vec_dialog.size())
		{
			dialogue_index = 0;
		}
		}
		b_indexDebounce = true;
		isPressed = true;


	}
	// NPC Text Reset
	if ((!Application::IsKeyPressed('E') && b_indexDebounce == true) || collision(player_pos, pos, chat_boundary) == false)
	{
		b_indexDebounce = false;
	}
	if (collision(player_pos, pos, chat_boundary) == false)
	{
		isPressed = false;
	}
}