#ifndef DIALOGUE_H
#define DIALOGUE_H
#include <string>
#include <vector>
#include <fstream>
#include "Vector3.h"

using std::ifstream;
using std::vector;
using std::string;


typedef struct Dialogue
{
	/*---n_row refers to row---*/
	/*<---n_col refers to column---*/
	int n_row, n_col;
	char** data;

	// Default Constructor
	Dialogue(int row, int col)
	{
		int i;
		n_row = row;
		n_col = col;
		data = new char*[n_row];
		for (i = 0; i < n_row; i++)
		{
			data[i] = new char[n_col + 1];
		}
	}
	// Default Destructor
	~Dialogue()
	{
		int i = 0;
		n_row = n_col = 0;
		for (i = 0; i < n_row; i++)
		{
			delete[]data[i];
		}
		delete[]data;
	}
};

char** Dialogue(int d);

#endif