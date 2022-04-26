#include "Adapters.h"

void Adapters::Init(std::string str_filepath)
{
	std::fstream file_outputs;
	char ch_buffer[256];
	int i_output;
	int i_max = 0;

	file_outputs.open(str_filepath);

	while (!file_outputs.eof())
	{
		file_outputs.getline(ch_buffer, 256);
		i_output = atoi(ch_buffer);
		i_max = std::max(i_max, i_output);
		v_adaptersOutputs.push_back(i_output);
	}

	i_builtInAdapter = i_max + 3;
}

bool Adapters::IsExisting(int i_output)
{
	if (i_output == i_builtInAdapter)
		return true;
	for (auto i_value : v_adaptersOutputs)
	{
		if (i_value == i_output)
			return true;
	}
	return false;
}

int Adapters::GetThexJoltDiffNumber(int i_difference)
{
	int i_count = 0;
	bool isValid = true;

	// first output = 0
	for (int i = 1; i < i_difference; i++)
	{
		if (IsExisting(i))
			isValid = false;
	}
	isValid = isValid && IsExisting(i_difference);
	if (isValid)
		i_count++;

	for (auto i_value : v_adaptersOutputs)
	{
		isValid = true;
		for (int i = 1; i < i_difference; i++)
		{
			if (IsExisting(i_value + i))
				isValid = false;
		}

		isValid = isValid && IsExisting(i_value + i_difference);

		if (isValid)
			i_count++;

	}
	return i_count;
}

unsigned long long Adapters::GetTheNumberOfCombinationsFrom(int i_start)
{
	unsigned long long i_count = 1;
	int i_lastStop = i_start;
	int i_nextStop = i_start;

	while (i_lastStop != i_builtInAdapter)
	{
		i_nextStop = FindTheNext3diff(i_lastStop);
		i_count *= GetTheNumberOfCombinationsFromTo(i_lastStop, i_nextStop);
		i_lastStop = i_nextStop;
	}

	return i_count;
}

unsigned long Adapters::GetTheNumberOfCombinationsFromTo(int i_start, int i_last)
{
	unsigned long i_count = 0;

	if (i_start == i_last)
		i_count = 1;
	else
	{
		if (IsExisting(i_start + 1))
			i_count += GetTheNumberOfCombinationsFromTo(i_start + 1, i_last);

		if (IsExisting(i_start + 2))
			i_count += GetTheNumberOfCombinationsFromTo(i_start + 2, i_last);

		if (IsExisting(i_start + 3))
			i_count += GetTheNumberOfCombinationsFromTo(i_start + 3, i_last);
	}

	return i_count;
}

int Adapters::FindTheNext3diff(int i_start)
{
	int i_bestAnswer = i_builtInAdapter;

	for (auto i_value : v_adaptersOutputs)
	{
		if (i_value <= i_start || i_value >= i_bestAnswer)
		{

		}
		else
		{
			if (IsExisting(i_value + 3) && !IsExisting(i_value + 2) && !IsExisting(i_value + 1))
				i_bestAnswer = std::min(i_bestAnswer, i_value);
		}
	}
	return i_bestAnswer;
}