/******************************************************************************/
/*!
\file	Music.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Class to define the music
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
Class Music:
\brief
Class for the overall music in the game
*/
/******************************************************************************/
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