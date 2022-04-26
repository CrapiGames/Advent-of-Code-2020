#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Utility.h"

class GroupAnswers;
class DeclarationFormAnswers;


class DeclarationFormAnswers
{
public:
	std::vector<GroupAnswers*> v_everyGroupAnswers;

	void Init(std::string str_filepath);
	int GetTheSumOfCounts_Anyone();
	int GetTheSumOfCounts_Everyone();
	void AddGroupAnswers(std::string str_GroupAnswers);
};

class GroupAnswers
{
public:
	std::vector<std::string> v_str_personAnswers;

	void Init(std::string str_groupAnswers);
	std::string GetCollectedAnswers_Anyone();
	std::string GetCollectedAnswers_Everyone();
};
