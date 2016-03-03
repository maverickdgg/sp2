/******************************************************************************/
/*!
\file	Map.h
\author Daniel Chua
\par	Email: 152112Y\@mymail.nyp.edu.sg
\par	Admin Number: 152112Y
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9025 8239
\brief
Class to handle the dynamic construction of arrays used for maps
*/
/******************************************************************************/
#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>
#include <iostream>

#include "Vector3.h"

using std::string;
/******************************************************************************/
/*!
Struct sMap:
\brief
Struct for Map
/******************************************************************************/
typedef struct sMap
{
	int nrow, ncol;
	char* data;

	//constructor
	sMap(int row, int col)
	{
		nrow = row;
		ncol = col;
		
		data = new char[(nrow*ncol)];
	}
	//destructor
	~sMap()
	{
		delete []data;
	}

}MAP,*PMAP;

PMAP load_map(string filename);

Vector3 indexToVector(int index);
int vectorToIndex(Vector3 pos);
int toIndex(int row, int col);

#endif