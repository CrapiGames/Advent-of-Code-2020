#pragma once
#include <fstream>
#include <string>

constexpr auto SIZE = 20;

struct ConwayCubes3D
{
	bool a_isActive[SIZE][SIZE][SIZE];

	void Init(std::string str_filepath);
	void Init(bool aisActive[SIZE][SIZE][SIZE]);

	int GetSumOfActiveNeighbors(int i_x, int i_y, int i_z);
	void DoACycle();
	int GetSumOfActive();
	int GetSumOfActiveAfterCycles(int i_numberOfCycles);

};

struct ConwayCubes4D
{
	bool a_isActive[SIZE][SIZE][SIZE][SIZE];

	void Init(std::string str_filepath);
	void Init(bool aisActive[SIZE][SIZE][SIZE][SIZE]);

	int GetSumOfActiveNeighbors(int i_x, int i_y, int i_z, int i_w);
	void DoACycle();
	int GetSumOfActive();
	int GetSumOfActiveAfterCycles(int i_numberOfCycles);

};