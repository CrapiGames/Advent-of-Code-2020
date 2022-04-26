#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

class ElvesGame
{
public:
	int i_IdOfLastElement;
	int i_lastNumber;
	std::unordered_map<int, int> memory;

	void Init(std::vector<int> v_i_startingNumbers);
	int GetXthNumber(size_t i_X);
};