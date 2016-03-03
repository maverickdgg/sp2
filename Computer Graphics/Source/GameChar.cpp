/******************************************************************************/
/*!
\file GameChar.cpp
\author Daniel
\brief Abstract class reserved for game characters only
*/
/******************************************************************************/

#include "GameChar.h"
#include <iostream>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

size_t GameChar::GC_count = 0;

/******************************************************************************/
/*!
\brief
Default constructor that has a count which increments everytime a character is declared, a distance in which chat is initiated, two boolean to check during chat with NPCs so it can be restarted as well as read from txt files
*/
/******************************************************************************/

GameChar::GameChar()
{
	chat_boundary = 20;
	GC_count++;
	b_indexDebounce = false;
	dialogue_index = 0;
	b_dialogueEnd = false;
}

/******************************************************************************/
/*!
\brief
Overloaded constructor that delegates variables such as name and position to GameObject constructor and initialise health amount of character
\param object_name
String type variable to store name of character
\param boundary
Int type var to detect collision distance of player from object
\param viewAngle
Float type var to store angle of rotation of object
\param pos
Vector3 type var to store x-y-z position of object
\param init_health
unsigned short type var to store initialise initial health of game char
*/
/******************************************************************************/

GameChar::GameChar(string object_name, int boundary, float viewAngle, Vector3 pos, smaller init_Health) : GameObject(object_name, boundary, viewAngle, pos), health(init_Health)
{
	chat_boundary = 20;
	++GC_count;
	dialogue_index = 0;
	b_indexDebounce = false;
	b_dialogueEnd = false;
}

/******************************************************************************/
/*!
\brief
Default destructor that decrements when an object of the class is deleted
*/
/******************************************************************************/

GameChar::~GameChar()
{
	--GC_count;
}

/******************************************************************************/
/*!
\brief 
    Read from text file to extract string dialog using fStream
\param link
    String type var to access direct link to a text file
\exception
    Direct link is not found and therefore contents cannot be read
\return
    Vector of strings
*/
/******************************************************************************/

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

/******************************************************************************/
/*!
\brief Standard interactions with NPC 
\param player_pos
    Vector3 type var to decide when collision occurs between player and NPC so chat interaction is triggered
*/
/******************************************************************************/

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

/******************************************************************************/
/*!
\brief Gets health of character
\return
    Character's current health in unsigned short
*/
/******************************************************************************/

smaller GameChar::getHealth()
{
	return health;
}

/******************************************************************************/
/*!
\brief Gets health of char by converting it to string
\exception
    Player's health is an ascii character other than the alphabet after "+'0'"
\return
    Character's current health in string
*/
/******************************************************************************/

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
    if (health <= 0)
        health = 0;
	return replace;
}

/******************************************************************************/
/*!
\brief Checks whether character is deceased if health is less than or equal to 0
\return
    True if dead, false if not
*/
/******************************************************************************/

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

/******************************************************************************/
/*!
\brief Character recieves damage
\param damage
    amount of damage in int taken
\exception
    if character's health is already less than 0, health will not reach the negative range
\exception
    if damage is less than 0, return false
\return
    whether character has recieved damaged
Character's current health in unsigned short
*/
/******************************************************************************/

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

/******************************************************************************/
/*!
\brief Heals the character by a certain amount
\param healAMT
    int to represent amount of health gained back
*/
/******************************************************************************/

void GameChar::regainHealth(const int& healAMT)
{
	if (health <= 100)
	{
		health += healAMT;
		if (health > 100)
		{
			health = 100;
		}
	}
}

/******************************************************************************/
/*!
\brief Assigns quest to character
*/
/******************************************************************************/

void GameChar::assignQuest(Quest* q)
{
	quest = q;
}

