#include "Utility.h"


bool CompareStrings(std::string string1, std::string string2)
{
	return string1.compare(string2) == 0;
}

bool CompareStrings(std::string string1, int posString1, int sizeString1, std::string string2)
{
	return string1.compare(posString1, sizeString1, string2) == 0;
}

bool CompareStrings(std::string string1, int posString1, int sizeString1, std::string string2, int posString2, int sizeString2)
{
	return string1.compare(posString1, sizeString1, string2, posString2, sizeString2) == 0;
}

bool CompareValueInRangeIncluded(int value, int rangeMin, int rangeMax)
{
	return value >= rangeMin && value <= rangeMax;
}

std::string GetACopy(std::string string, int pos0, int size)
{
	std::string stringOutput = "";
	stringOutput = string[pos0];

	for (int i = 1; i < size; i++)
	{
		stringOutput += string[pos0 + i];
	}
	return stringOutput;
}