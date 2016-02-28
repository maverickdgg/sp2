#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>
#include <iostream>

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
		
		/*for (int i = 0; i < nrow; ++i)
		{
			for (int j = 0; j < ncol; ++j)
			{
				data = new char;
			}
		}*/
		data = new char[nrow * ncol];
	}
	//destructor
	~sMap()
	{
		delete []data;
	}

}MAP,*PMAP;

PMAP load_map(string filename);

#endif