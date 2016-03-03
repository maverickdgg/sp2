/******************************************************************************/
/*!
\file	Quest.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define Quests
*/
/******************************************************************************/
#ifndef QUEST_H
#define QUEST_H

#include <vector>
#include <string>
#include "GameObject.h"

using std::vector;
using std::string;
/******************************************************************************/
/*!
Class Quest:
\brief
Class for Quests
/******************************************************************************/
class Quest
{
public:
	Quest();
	Quest(int numOfTasks, vector<string> names, string questName);
	~Quest();
	vector<bool> task; // Objective Complete
	int numTasks;
	vector<string> taskNames;
	string questName;

	void taskComplete(int index);
	bool questComplete();
	//vector<string> ReadFromTxt(string link);
	void ReadFromTxtQuest(string link);
};

#endif