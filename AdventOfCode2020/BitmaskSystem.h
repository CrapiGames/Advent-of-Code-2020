#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "Utility.h"

class BitmaskSystem
{
public:
	long long int i_maskValue0;
	long long int i_maskValue1;
	long long int i_maskValueX;
	std::vector<long long int> v_i_memoryAdress;
	std::vector<long long int> v_i_memoryData;
	std::vector<std::string> v_str_programInstructions;

	void Init(std::string str_filepath);
	void TreatInstruction_Part1(std::string str_instruction);
	void TreatInstruction_Part2(std::string str_instruction);
	long long int GetResultFromBitmask(long long int i_value);
	std::vector<long long int> GetAdressesFromBitmask(long long int i_value);
	long long int GetSumOfMemoryDataAfterProcessing_Part1();
	long long int GetSumOfMemoryDataAfterProcessing_Part2();

};