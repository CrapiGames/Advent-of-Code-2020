#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Utility.h"

class TreeMap
{
public:
	std::vector<std::string> v_str_mapFull;
	int i_nbOfColumns;
	int i_nbOfLines;

	void Init(std::string str_filepath);
	bool IsATree(int i_lineFromTop, int i_columnFromLeft);
	int CountTreesWithSlope(int i_downMove, int i_rightMove);
};

