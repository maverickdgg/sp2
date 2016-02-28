#include "Map.h"

PMAP load_map(string filename)
{
	PMAP map;
	std::ifstream infile;
	int row, col, i;

	infile.open(filename, std::ifstream::in);
	if (!infile)
	{
		std::cout << "Error Opening" << filename << std::endl;
		exit(1);
	}

	if (infile.good())
	{
		// get the number of rows and column from the first line of the text file.
		infile >> row >> col;
		//allocate memory based on the map structure to hold the map data.
		map = new MAP(row, col);
		i = 0;
		while (infile.good())
		{
			string line;
			getline(infile, line);

			if (line.length())
			{
				for (int j = 0; j < col; ++j)
				{
					//copying data;
					map->data[(i*col) + j] = line[j];
				}
				++i;
			}

		}

	}
	infile.close();

	return map;
}

Vector3 indexToVector(int index)
{
	int row, col;
	row = index / 50;
	col = index % 50;
	Vector3 origin = Vector3(-500, 0, -500);
	return (origin + Vector3(row * 20, 0, col * 20) );
}

int vectorToIndex(Vector3 pos)
{
	int row = (pos.x + 500) / 20;
	int col = (pos.z + 500) / 20;
	return (row * 50 + col);
}

int toIndex(int row, int col)
{
	return (row * 50 + col);
}