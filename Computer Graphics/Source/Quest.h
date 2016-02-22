#ifndef QUEST_H
#define QUEST_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class Quest
{
public:
	Quest();
	Quest(int numOfTasks,vector<string> names, string questName);
	~Quest();
	vector<bool> task; // Objective Complete
	vector<string> taskNames;
	string questName;

	void taskComplete(int index);
	bool questComplete();
};

#endif