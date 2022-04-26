#include "ColorBagRules.h"

void ColorBagRules::Init(std::string str_filepath)
{
	ColorBag *colorBag;
	std::fstream file_colorBagRules;
	char ch_buffer[1000];
	std::string str_fullLine;
	std::string str_colorID = "";
	std::string str_colorBagRule = "";
	size_t pos;
	file_colorBagRules.open(str_filepath);

	while (!file_colorBagRules.eof())
	{
		file_colorBagRules.getline(ch_buffer, 1000);
		str_fullLine = ch_buffer;
		pos = str_fullLine.find("contain", 0);

		std::string str_colorID = "";
		std::string str_colorBagRule = "";
		for (size_t i = 0; i < pos - 6; i++)
			str_colorID += str_fullLine[i];
		for (size_t i = pos + 8; i < str_fullLine.size(); i++)
			str_colorBagRule += str_fullLine[i];

		colorBag = new ColorBag();
		colorBag->Init(str_colorID, str_colorBagRule);

		v_colorBags.push_back(colorBag);
	}
}

int ColorBagRules::GetNumberColorBagsThatCouldContain(std::string str_colorIDToFind)
{
	std::vector<std::string> colorBagsFound;
	std::string str_colorIDToDo;
	bool is_alreadyFound = true;
	int i_lastlyDone = -1;

	while (i_lastlyDone < static_cast<int>(colorBagsFound.size()))
	{
		if (i_lastlyDone == -1)
			str_colorIDToDo = str_colorIDToFind;
		else
			str_colorIDToDo = colorBagsFound[i_lastlyDone];

		for (auto& colorBag : v_colorBags)
		{
			if (colorBag->IsContainingThis(str_colorIDToDo))
			{
				is_alreadyFound = false;
				for (auto str_colorBagfound : colorBagsFound)
				{
					is_alreadyFound = is_alreadyFound || CompareStrings(colorBag->str_colorID, str_colorBagfound);
				}
				if (!is_alreadyFound)
				{
					colorBagsFound.push_back(colorBag->str_colorID);
				}
			}
		}
		i_lastlyDone++;

	}
	return colorBagsFound.size();
}

int ColorBagRules::GetNumberOfBagsContained(std::string str_colorIDToFind)
{
	int i_count = 0;
	bool is_found = false;
	ColorBag *colorBagToTreat = v_colorBags[0];

	for (auto ColorBag : v_colorBags)
	{
		if (CompareStrings(ColorBag->str_colorID, str_colorIDToFind))
		{
			colorBagToTreat = ColorBag;
			is_found = true;
		}
	}

	if (is_found && colorBagToTreat->IsContaining)
	{
		for (auto str_colorContained : colorBagToTreat->v_str_colorContained)
		{
			i_count += 1 + GetNumberOfBagsContained(str_colorContained);
		}
	}
	else
		i_count = 0;

	return i_count;
}

void ColorBag::Init(std::string str_CcolorID, std::string str_CcolorBagRule)
{
	str_colorID = str_CcolorID;
	std::string str_colorIdContained;
	size_t pos_number = 0;
	size_t pos_bag = 0;
	int number = 0;

	if (CompareStrings(str_CcolorBagRule, "no other bags."))
		IsContaining = false;
	else
	{
		IsContaining = true;
		pos_bag = str_CcolorBagRule.find("bag", pos_bag + 1);
		while (pos_bag < str_CcolorBagRule.size())
		{
			if (pos_bag == std::string::npos)
				pos_bag = str_CcolorBagRule.size();

			number = atoi(&str_CcolorBagRule[pos_number]);
			
			str_colorIdContained = "";
			for (size_t i = pos_number + 2; i < pos_bag - 1; i++)
			{
				str_colorIdContained += str_CcolorBagRule[i];
			}


			for (int i = 0; i < number; i++)
			{
				v_str_colorContained.push_back(str_colorIdContained);
			}

			if (CompareStrings(str_CcolorBagRule, pos_bag + 3, 1, "s"))
				pos_number = pos_bag + 6;
			else
				pos_number = pos_bag + 5;

			pos_bag = str_CcolorBagRule.find("bag", pos_bag + 1);

		}
	}

}

bool ColorBag::IsContainingThis(std::string str_colorIDToFind)
{
	if (!IsContaining)
		return false;
	else
	{
		for (auto str_colorIdContained : v_str_colorContained)
		{
			if (CompareStrings(str_colorIdContained, str_colorIDToFind))
				return true;
		}
		return false;
	}
}