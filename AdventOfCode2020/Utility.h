#pragma once

#include <string>

bool CompareStrings(std::string string1, std::string string2);
bool CompareStrings(std::string string1, int posString1, int sizeString1, std::string string2);
bool CompareStrings(std::string string1, int posString1, int sizeString1, std::string string2, int posString2, int sizeString2);

bool CompareValueInRangeIncluded(int value, int rangeMin, int rangeMax);

std::string GetACopy(std::string string, int pos0, int size);