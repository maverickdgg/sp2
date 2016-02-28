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

