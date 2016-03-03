#include "Music.h"

Music::Music()
{
}

Music::~Music()
{

}

vector<string> Music::readFromText(string link)
{
	ifstream inData;
	inData.open(link, std::ifstream::in);
	vector<string> vec_dialog;

	if (!inData)
	{
		std::cout << "Error Opening" << link << std::endl;
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

void Music::Init()
{
	engine = irrklang::createIrrKlangDevice();
	musicVec = readFromText("text//soundName.txt");


	int i = 0;
	for (vector<string>::iterator it = musicVec.begin(); it != musicVec.end(); ++it)
	{
		sound.push_back(engine->addSoundSourceFromFile((*it).c_str()) );
		sound[i]->setDefaultVolume(1.f);
		++i;
	}

}

void Music::OpeningMusic(int index,bool loop)
{
	engine->play2D(sound[index], loop);
}