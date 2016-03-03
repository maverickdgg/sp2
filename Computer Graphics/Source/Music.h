#ifndef MUSIC_H
#define MUSIC_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>


#include "../irrKlang/include/irrKlang.h"

using std::vector;
using std::string;
using std::ifstream;

class Music
{
public:
	Music();
	~Music();

	void Init();
	vector<string> readFromText(string link);
	void OpeningMusic(int index,bool loop);

	irrklang::ISoundEngine* engine;
	vector<irrklang::ISoundSource*> sound;
	vector<string> musicVec;

};


#endif