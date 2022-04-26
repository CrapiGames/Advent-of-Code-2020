#include "TreeMap.h"


void TreeMap::Init(std::string str_filepath)
{
	std::fstream file_mapfull;
	char ch_line[256];
	std::string str_line;

	file_mapfull.open(str_filepath);
	while (!file_mapfull.eof())
	{
		file_mapfull.getline(ch_line, 256);
		str_line = ch_line;
		v_str_mapFull.push_back(str_line);
	}
	i_nbOfLines = v_str_mapFull.size();
	i_nbOfColumns = v_str_mapFull[0].size();
}

bool TreeMap::IsATree(int i_lineFromTop, int i_columnFromLeft)
{
	if (i_lineFromTop >= i_nbOfLines)
		return false;

	return CompareStrings(v_str_mapFull[i_lineFromTop], i_columnFromLeft % i_nbOfColumns, 1, "#");
}

int TreeMap::CountTreesWithSlope(int i_downMove, int i_rightMove)
{
	int i_rightPos = 0;
	int i_downPos = 0;
	int i_nbOfTrees = 0;

	while (i_downPos < i_nbOfLines)
	{
		i_downPos += i_downMove;
		i_rightPos += i_rightMove;
		if (IsATree(i_downPos, i_rightPos))
			i_nbOfTrees++;
	}

	return i_nbOfTrees;
}