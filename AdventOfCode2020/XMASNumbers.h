#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class XMASNumbers
{
public:
	std::vector<int> v_numbers;
	int preambleSize;

	void Init(std::string str_filepath, int i_preambleSize);
	bool Is_Valid(size_t i_pos);
	int FindTheFirst();
	int FintTheEncryptionWeakness(int i_condition);

};