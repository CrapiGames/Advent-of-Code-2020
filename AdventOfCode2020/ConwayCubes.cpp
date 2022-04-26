#include "ConwayCubes.h"


void ConwayCubes3D::Init(std::string str_filepath)
{
	std::fstream file_cubes;
	char ch_buffer[256];
	std::string str_buffer;
	size_t i_count = 0;

	file_cubes.open(str_filepath);

	for (int i_x = 0; i_x < SIZE; i_x++)
	{
		for (int i_y = 0; i_y < SIZE; i_y++)
		{
			for (int i_z = 0; i_z < SIZE; i_z++)
			{
				a_isActive[i_z][i_x][i_y] = false;
			}
		}
	}

	while (!file_cubes.eof())
	{
		file_cubes.getline(ch_buffer, 256);
		str_buffer = ch_buffer;

		for (size_t i = 0; i < str_buffer.size(); i++)
		{
			if (str_buffer[i] == '#')
				a_isActive[SIZE / 2][SIZE / 2 - static_cast<int>(str_buffer.size() / 2) + i][SIZE / 2 + static_cast<int>(str_buffer.size() / 2) - i_count] = true;
		}
		i_count++;
	}
}

void ConwayCubes3D::Init(bool aisActive[SIZE][SIZE][SIZE])
{

	for (int i_x = 0; i_x < SIZE; i_x++)
	{
		for (int i_y = 0; i_y < SIZE; i_y++)
		{
			for (int i_z = 0; i_z < SIZE; i_z++)
			{
				a_isActive[i_z][i_x][i_y] = aisActive[i_z][i_x][i_y];
			}
		}
	}
}

void ConwayCubes3D::DoACycle()
{
	bool aisActive[SIZE][SIZE][SIZE] = { false };

	for (int i_x = 1; i_x < SIZE - 1; i_x++)
	{
		for (int i_y = 1; i_y < SIZE - 1; i_y++)
		{
			for (int i_z = 1; i_z < SIZE - 1; i_z++)
			{
				if (a_isActive[i_z][i_x][i_y] && (GetSumOfActiveNeighbors(i_x, i_y, i_z) == 2 || GetSumOfActiveNeighbors(i_x, i_y, i_z) == 3))
					aisActive[i_z][i_x][i_y] = true;
				else if (!a_isActive[i_z][i_x][i_y] && GetSumOfActiveNeighbors(i_x, i_y, i_z) == 3)
					aisActive[i_z][i_x][i_y] = true;
			}
		}
	}

	Init(aisActive);
}

int ConwayCubes3D::GetSumOfActiveNeighbors(int i_x, int i_y, int i_z)
{
	int i_result = 0;

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			for (int dz = -1; dz <= 1; dz++)
			{
				if (dx == 0 && dy == 0 && dz == 0)
					continue;
				else if (a_isActive[i_z + dz][i_x + dx][i_y + dy])
					i_result++;
			}
		}
	}
	return i_result;
}

int ConwayCubes3D::GetSumOfActive()
{
	int i_result = 0;

	for (int i_x = 0; i_x < SIZE; i_x++)
	{
		for (int i_y = 0; i_y < SIZE; i_y++)
		{
			for (int i_z = 0; i_z < SIZE; i_z++)
			{
				if (a_isActive[i_z][i_x][i_y])
					i_result++;
			}
		}
	}

	return i_result;
}

int ConwayCubes3D::GetSumOfActiveAfterCycles(int i_numberOfCycles)
{
	for (int i = 0; i < i_numberOfCycles; i++)
		DoACycle();

	return GetSumOfActive();
}

#include "ConwayCubes.h"


void ConwayCubes4D::Init(std::string str_filepath)
{
	std::fstream file_cubes;
	char ch_buffer[256];
	std::string str_buffer;
	size_t i_count = 0;

	file_cubes.open(str_filepath);

	for (int i_x = 0; i_x < SIZE; i_x++)
	{
		for (int i_y = 0; i_y < SIZE; i_y++)
		{
			for (int i_z = 0; i_z < SIZE; i_z++)
			{
				for (int i_w = 0; i_w < SIZE; i_w++)
				{
					a_isActive[i_w][i_z][i_x][i_y] = false;
				}
			}
		}
	}

	while (!file_cubes.eof())
	{
		file_cubes.getline(ch_buffer, 256);
		str_buffer = ch_buffer;

		for (size_t i = 0; i < str_buffer.size(); i++)
		{
			if (str_buffer[i] == '#')
				a_isActive[SIZE / 2][SIZE / 2][SIZE / 2 - static_cast<int>(str_buffer.size() / 2) + i][SIZE / 2 + static_cast<int>(str_buffer.size() / 2) - i_count] = true;
		}
		i_count++;
	}
}

void ConwayCubes4D::Init(bool aisActive[SIZE][SIZE][SIZE][SIZE])
{

	for (int i_x = 0; i_x < SIZE; i_x++)
	{
		for (int i_y = 0; i_y < SIZE; i_y++)
		{
			for (int i_z = 0; i_z < SIZE; i_z++)
			{
				for (int i_w = 0; i_w < SIZE; i_w++)
				{
					a_isActive[i_w][i_z][i_x][i_y] = aisActive[i_w][i_z][i_x][i_y];
				}
			}
		}
	}
}

void ConwayCubes4D::DoACycle()
{
	bool aisActive[SIZE][SIZE][SIZE][SIZE] = { false };

	for (int i_x = 1; i_x < SIZE - 1; i_x++)
	{
		for (int i_y = 1; i_y < SIZE - 1; i_y++)
		{
			for (int i_z = 1; i_z < SIZE - 1; i_z++)
			{
				for (int i_w = 1; i_w < SIZE - 1; i_w++)
				{
					if (a_isActive[i_w][i_z][i_x][i_y] && (GetSumOfActiveNeighbors(i_x, i_y, i_z, i_w) == 2 || GetSumOfActiveNeighbors(i_x, i_y, i_z, i_w) == 3))
						aisActive[i_w][i_z][i_x][i_y] = true;
					else if (!a_isActive[i_w][i_z][i_x][i_y] && GetSumOfActiveNeighbors(i_x, i_y, i_z, i_w) == 3)
						aisActive[i_w][i_z][i_x][i_y] = true;
				}
			}
		}
	}

	Init(aisActive);
}

int ConwayCubes4D::GetSumOfActiveNeighbors(int i_x, int i_y, int i_z, int i_w)
{
	int i_result = 0;

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			for (int dz = -1; dz <= 1; dz++)
			{
				for (int dw = -1; dw <= 1; dw++)
				{
					if (dx == 0 && dy == 0 && dz == 0 && dw == 0)
						continue;
					else if (a_isActive[i_w + dw][i_z + dz][i_x + dx][i_y + dy])
						i_result++;
				}
			}
		}
	}
	return i_result;
}

int ConwayCubes4D::GetSumOfActive()
{
	int i_result = 0;

	for (int i_x = 0; i_x < SIZE; i_x++)
	{
		for (int i_y = 0; i_y < SIZE; i_y++)
		{
			for (int i_z = 0; i_z < SIZE; i_z++)
			{
				for (int i_w = 0; i_w < SIZE; i_w++)
				{
					if (a_isActive[i_w][i_z][i_x][i_y])
						i_result++;
				}
			}
		}
	}

	return i_result;
}

int ConwayCubes4D::GetSumOfActiveAfterCycles(int i_numberOfCycles)
{
	for (int i = 0; i < i_numberOfCycles; i++)
		DoACycle();

	return GetSumOfActive();
}