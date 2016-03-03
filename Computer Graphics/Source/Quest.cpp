#include "Quest.h"

Quest::Quest()
{
}
/******************************************************************************/
/*!
\brief
overloaded constructor of the quest
*/
/******************************************************************************/
Quest::Quest(int numOfTasks, vector<string> names, string questName)
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
/******************************************************************************/
/*!
\brief
complete the task
\param index
index of the task 
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
check if all task are done and quest is complete
\return
true if all task complete
*/
/******************************************************************************/
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

void Quest::ReadFromTxtQuest(string link)
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
		smaller index = 1;
		while (inData.good())
		{
			string data;
			if (index == 1)
			{
				std::getline(inData, data);
				taskNames.push_back(data);
			}
			else if (index == 2)
			{
				std::getline(inData, data);
				questName = data;
			}
			++index;

		}
	}
	inData.close();
}