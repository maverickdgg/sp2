#include "GameChar.h"
#include <iostream>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

size_t GameChar::GC_count = 0;

GameChar::GameChar()
{
	chat_boundary = 20;
	GC_count++;
	b_indexDebounce = false;
	dialogue_index = 0;
	b_dialogueEnd = false;
}

GameChar::GameChar(string object_name, int boundary, float viewAngle, Vector3 pos, smaller init_Health) : GameObject(object_name, boundary, viewAngle, pos), health(init_Health)
{
	chat_boundary = 20;
	++GC_count;
	dialogue_index = 0;
	b_indexDebounce = false;
	b_dialogueEnd = false;
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
	inData.close();
	return vec_dialog;
}

void GameChar::chat_update(Vector3 player_pos)
{
	// NPC Text Indexing
	if (vec_dialog.empty() == false)
	{
		if (Application::IsKeyPressed('E') && b_indexDebounce == false && collision(player_pos, pos, 15 + this->boundary + chat_boundary) == true)
		{
			if (isPressed == true && b_dialogueEnd == false)
			{
				++dialogue_index;
				if (dialogue_index >= vec_dialog.size())
				{
					--dialogue_index;
					b_dialogueEnd = true;
				}
			}
			b_indexDebounce = true;
			isPressed = true;


		}
		// NPC Text Reset
		if ((!Application::IsKeyPressed('E') && b_indexDebounce == true) || collision(player_pos, pos, 15 + this->boundary + chat_boundary) == false)
		{
			b_indexDebounce = false;
		}
		if (collision(player_pos, pos, 15 + this->boundary + chat_boundary) == false)
		{
			isPressed = false;
			b_dialogueEnd = false;
			dialogue_index = 0;
		}
	}

}

smaller GameChar::getHealth()
{
	return health;
}

string GameChar::getHealthString()
{
	string replace;
	if (health / 100 != 0)
	{
		replace = (health / 100) + '0';
		replace += ((health / 10) % 10) + '0';
		replace += (health % 10) + '0';
	}
	else if (health / 100 == 0 && health / 10 != 0)
	{
		replace = (health / 10) + '0';
		replace += (health % 10) + '0';
	}
	else
		replace = health + '0';
	return replace;
}

bool GameChar::isDead()
{
	if (health <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameChar::recieveHealthDamage(const int& damage)
{
	if (isDead() == true)
	{
		health = 0;
		return false;
	}
	else if (health > 0)
	{
		health -= damage;
		return true;
	}
	
}

void GameChar::regainHealth(const int& healAMT)
{
	if (health > 100)
	{
		health = 100;
	}
	if (health <= 100)
	{
		health =+ healAMT;
	}
}

void GameChar::assignQuest(Quest* q)
{
	quest = q;
}

