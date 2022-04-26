#include "BitmaskSystem.h"


void BitmaskSystem::Init(std::string str_filepath)
{
	std::fstream file_instructions;
	char ch_buffer[256];
	std::string str_instruction;
	v_str_programInstructions.clear();
	v_i_memoryAdress.clear();
	v_i_memoryData.clear();

	file_instructions.open(str_filepath);
	while (!file_instructions.eof())
	{
		file_instructions.getline(ch_buffer, 256);
		str_instruction = ch_buffer;
		v_str_programInstructions.push_back(str_instruction);
	}
}

void BitmaskSystem::TreatInstruction_Part1(std::string str_instruction)
{
	size_t i_pos;
	std::string str_buffer;
	int i_adress;
	long long int i_value;
	bool hasBeenDone = false;

	if (CompareStrings(str_instruction, 0, 3, "mem"))
	{
		i_pos = str_instruction.find(']');
		str_buffer = "";
		for (size_t i = 4; i < i_pos; i++)
			str_buffer += str_instruction[i];
		i_adress = stoi(str_buffer);
		str_buffer = "";
		for (size_t i = i_pos + 4; i < str_instruction.size(); i++)
			str_buffer += str_instruction[i];
		i_value = stoi(str_buffer);

		i_value = GetResultFromBitmask(i_value);

		for (size_t i = 0; i < v_i_memoryAdress.size(); i++)
		{
			if (v_i_memoryAdress[i] == i_adress)
			{
				v_i_memoryData[i] = i_value;
				hasBeenDone = true;
			}
		}
		if (!hasBeenDone)
		{
			v_i_memoryAdress.push_back(i_adress);
			v_i_memoryData.push_back(i_value);
		}
	}
	else if (CompareStrings(str_instruction, 0, 4, "mask"))
	{
		i_pos = 7;
		str_buffer = "";
		i_maskValue0 = 0;
		i_maskValue1 = 0;

		for (size_t i = i_pos; i < str_instruction.size(); i++)
			str_buffer += str_instruction[i];
		for (size_t i = 0; i < str_buffer.size(); i++)
		{
			if (CompareStrings(str_buffer, str_buffer.size() - 1 - i, 1, "1"))
			{
				i_maskValue1 += (long long int) 1 << i;
				i_maskValue0 += (long long int) 1 << i;
			}
			else if (CompareStrings(str_buffer, str_buffer.size() - 1 - i, 1, "0"))
			{
				i_maskValue1 += 0 << i;
				i_maskValue0 += 0 << i;
			}
			else
			{
				i_maskValue1 += 0 << i;
				i_maskValue0 += (long long int) 1 << i;
			}
		}

	}

}

long long int BitmaskSystem::GetResultFromBitmask(long long int i_value)
{
	long long int i_result;
	i_result = i_value | i_maskValue1;
	i_result = i_result & i_maskValue0;
	return i_result;
}


long long int BitmaskSystem::GetSumOfMemoryDataAfterProcessing_Part1()
{
	long long int i_result = 0;

	for (size_t i = 0; i < v_str_programInstructions.size(); i++)
		TreatInstruction_Part1(v_str_programInstructions[i]);

	for (size_t i = 0; i < v_i_memoryAdress.size(); i++)
		i_result += v_i_memoryData[i];

	return i_result;

}

void BitmaskSystem::TreatInstruction_Part2(std::string str_instruction)
{
	size_t i_pos;
	std::vector<long long int> v_i_adresses;
	std::string str_buffer;
	long long int i_adressInput;
	long long int i_value;
	bool hasBeenDone = false;

	if (CompareStrings(str_instruction, 0, 3, "mem"))
	{
		i_pos = str_instruction.find(']');
		str_buffer = "";
		for (size_t i = 4; i < i_pos; i++)
			str_buffer += str_instruction[i];
		i_adressInput = stoi(str_buffer);
		str_buffer = "";
		for (size_t i = i_pos + 4; i < str_instruction.size(); i++)
			str_buffer += str_instruction[i];
		i_value = stoi(str_buffer);

		v_i_adresses = GetAdressesFromBitmask(i_adressInput);

		for (size_t i = 0; i < v_i_adresses.size(); i++)
		{
			hasBeenDone = false;
			for (size_t j = 0; j < v_i_memoryAdress.size(); j++)
			{
				if (v_i_memoryAdress[j] == v_i_adresses[i])
				{
					v_i_memoryData[j] = i_value;
					hasBeenDone = true;
					break;
				}
			}
			if (!hasBeenDone)
			{
				v_i_memoryAdress.push_back(v_i_adresses[i]);
				v_i_memoryData.push_back(i_value);
			}
		}
	}
	else if (CompareStrings(str_instruction, 0, 4, "mask"))
	{
		i_pos = 7;
		str_buffer = "";
		i_maskValue0 = 0;
		i_maskValue1 = 0;
		i_maskValueX = 0;

		for (size_t i = i_pos; i < str_instruction.size(); i++)
			str_buffer += str_instruction[i];
		for (size_t i = 0; i < str_buffer.size(); i++)
		{
			if (CompareStrings(str_buffer, str_buffer.size() - 1 - i, 1, "1"))
			{
				i_maskValue1 += (long long int) 1 << i;
				i_maskValue0 += (long long int) 1 << i;
			}
			else if (CompareStrings(str_buffer, str_buffer.size() - 1 - i, 1, "0"))
			{
				i_maskValue1 += 0 << i;
				i_maskValue0 += 0 << i;
			}
			else
			{
				i_maskValue1 += 0 << i;
				i_maskValue0 += (long long int) 1 << i;
				i_maskValueX += (long long int) 1 << i;
			}
		}

	}

}

std::vector<long long int> BitmaskSystem::GetAdressesFromBitmask(long long int i_value)
{
	std::vector<long long int> v_i_adresses;
	long long int i_unchangedAdress;
	int i = 0;
	size_t i_numberOfAdresses;

	i_unchangedAdress = i_value | i_maskValue1;
	i_unchangedAdress = i_unchangedAdress & ~i_maskValueX;
	v_i_adresses.push_back(i_unchangedAdress);

	while (((long long int) 1 << i) < i_maskValueX)
	{
		if ( (i_maskValueX & ((long long int)1 << i)) == (long long int) 1 << i)
		{
			i_numberOfAdresses = v_i_adresses.size();
			for (size_t j = 0; j < i_numberOfAdresses; j++)
			{
				v_i_adresses.push_back(v_i_adresses[j] + ( (long long int) 1 << i));
			}
		}
		i++;
	}

	return v_i_adresses;
}

long long int BitmaskSystem::GetSumOfMemoryDataAfterProcessing_Part2()
{
	long long int i_result = 0;

	for (size_t i = 0; i < v_str_programInstructions.size(); i++)
		TreatInstruction_Part2(v_str_programInstructions[i]);

	for (size_t i = 0; i < v_i_memoryAdress.size(); i++)
		i_result += v_i_memoryData[i];

	return i_result;

}