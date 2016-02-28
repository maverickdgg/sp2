#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>
#include <iostream>

#include "Vector3.h"

using std::string;

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