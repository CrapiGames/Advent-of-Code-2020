#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Adapters
{
public:
	std::vector<int> v_adaptersOutputs;
	int i_builtInAdapter;

	void Init(std::string str_filepath);
	bool IsExisting(int i_output);
	int GetThexJoltDiffNumber(int i_difference);
	unsigned long long GetTheNumberOfCombinationsFrom(int i_start);
	unsigned long GetTheNumberOfCombinationsFromTo(int i_start, int i_last);
	int FindTheNext3diff(int i_start);
};