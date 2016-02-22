#include "Quest.h"

Quest::Quest()
{
}

Quest::Quest(int numOfTasks, vector<string> names,string questName)
{
	for (int i = 0; i < numOfTasks; ++i)
	{
		task.push_back(false);
	}
	taskNames = names;
	this->questName = questName;
}

Quest::~Quest()
{
}

void Quest::taskComplete(int index)
{
	if (index >= task.size())
	{
		return;
	}
	else
	{
		task[index] = true;
	}
}

bool Quest::questComplete()
{
	for (vector<bool>::iterator it = task.begin(); it != task.end(); ++it)
	{
		if (*it == false)
		{
			return false;
		}
	}
	return true;
}