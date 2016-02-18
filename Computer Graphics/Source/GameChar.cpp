#include "GameChar.h"
#include <iostream>

using std::cout;
using std::endl;

size_t GameChar::GC_count = 0;

GameChar::GameChar()
{
	GC_count++;
}

GameChar::GameChar(string object_name, int boundary, float viewAngle, Vector3 pos) : GameObject(object_name, boundary, viewAngle, pos)
{
	++GC_count;
}

GameChar::~GameChar()
{
	--GC_count;
}

vector<string> GameChar::ReadFromTxt(string link)
{
	ifstream inData;
	inData.open(link,std::ifstream::in);
	
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
	//}
	inData.close();
	return vec_dialog;
}