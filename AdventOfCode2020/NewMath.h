#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


struct NewMath
{
	std::vector<std::string> v_str_equations;

	void Init(std::string str_filepath);
	long long int GetSolution_Part1(std::string str_equation);
	long long int GetSolutionWithoutParenthesis_Part1(std::string str_equation);
	long long int GetSolution_Part2(std::string str_equation);
	long long int GetSolutionWithoutParenthesis_Part2(std::string str_equation);
	long long int GetSolutionWithoutParenthesisNorPlus_Part2(std::string str_equation);
	long long int GetSumOfSolutions_Part1();
	long long int GetSumOfSolutions_Part2();
};