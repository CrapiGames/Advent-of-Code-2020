#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "Utility.h"

class ColorBag;
class ColorBagRules;


class ColorBagRules
{
public:
	std::vector<ColorBag*> v_colorBags;

	void Init(std::string str_filepath);

	int GetNumberColorBagsThatCouldContain(std::string str_colorIDToFind);
	int GetNumberOfBagsContained(std::string str_colorIDToFind);
};

class ColorBag
{
public:
	std::string str_colorID;
	std::vector<std::string> v_str_colorContained;
	bool IsContaining;

	void Init(std::string str_colorID, std::string str_colorBagRule);
	bool IsContainingThis(std::string str_colorIDToFind);
};