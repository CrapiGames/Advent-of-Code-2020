#include "XMASNumbers.h"

void XMASNumbers::Init(std::string str_filepath, int i_preambleSize)
{
	std::fstream file_numbers;
	char ch_buffer[256];
	int i_buffer;

	file_numbers.open(str_filepath);
	while (!file_numbers.eof())
	{
		file_numbers.getline(ch_buffer, 256);
		i_buffer = atoi(ch_buffer);
		v_numbers.push_back(i_buffer);
	}
	preambleSize = i_preambleSize;
}

bool XMASNumbers::Is_Valid(size_t i_pos)
{
	for (size_t i = i_pos - preambleSize ; i < i_pos; i++)
	{
		for (size_t j = i_pos - preambleSize; j < i_pos; j++)
		{
			if (i == j)
				;
			else if (v_numbers[i] + v_numbers[j] == v_numbers[i_pos])
				return true;
		}
	}
	return false;
}

int XMASNumbers::FindTheFirst()
{
	for (size_t i = preambleSize; i < v_numbers.size(); i++)
	{
		if (!Is_Valid(i))
			return v_numbers[i];
	}
	return -1;
}

int XMASNumbers::FintTheEncryptionWeakness(int i_condition)
{
	int i_sum = 0;
	size_t i_pos = 0;
	int i_min = 0;
	int i_max = 0;

	for (size_t i = 0; i < v_numbers.size() - 1; i++)
	{
		i_sum = v_numbers[i] + v_numbers[i + 1];
		i_pos = i+2;
		i_min = std::min(v_numbers[i], v_numbers[i + 1]);
		i_max = std::max(v_numbers[i], v_numbers[i + 1]);
		while (i_sum < i_condition && i_pos < v_numbers.size())
		{
			i_sum += v_numbers[i_pos];
			i_min = std::min(i_min, v_numbers[i_pos]);
			i_max = std::max(i_max, v_numbers[i_pos]);
			i_pos++;
		}

		if (i_sum == i_condition)
			return i_min + i_max;
	}
	return -1;
}