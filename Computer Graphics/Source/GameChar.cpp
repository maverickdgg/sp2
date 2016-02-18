#include "GameChar.h"

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

vector<string> GameChar::ReadFromTxt(string link, ifstream inData)
{
	inData.open("Image//Robotdialog.txt");
	//if (inData.is_open())
	//{
	string data;
		if (!inData.eof())
		{
			//inData.open(link); // associate & open files
			//if (inData.get() != ';')
			//{
			//	data = inData.get();
			//	vec_dialog.push_back(data);
			//}
			std::getline(inData, data);
			vec_dialog.push_back(data);
		}
	//}
	inData.close();
	return vec_dialog;
}