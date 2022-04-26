#include "NewMath.h"


void NewMath::Init(std::string str_filepath)
{
	std::fstream file_equations;
	char ch_buffer[1000];
	std::string str_equation;

	file_equations.open(str_filepath);

	while (!file_equations.eof())
	{
		file_equations.getline(ch_buffer, 1000);
		str_equation = ch_buffer;
		v_str_equations.push_back(str_equation);
	}
}

long long int NewMath::GetSolution_Part1(std::string str_equation)
{
	size_t i_posOpen = 0,i_posClose = 0;
	std::string str_newEquation = "";
	std::string str_insideParenthesis = "";
	char ch_buffer[256];

	for (size_t i = 0; i < str_equation.size(); i++)
	{
		if (str_equation[i] == '(')
		{
			i_posOpen = i;
		}
		else if (str_equation[i] == ')')
		{
			i_posClose = i;
			break;
		}
	}

	if (i_posClose == 0)
	{
		return GetSolutionWithoutParenthesis_Part1(str_equation);
	}

	for (size_t i = 0; i < i_posOpen; i++)
	{
		str_newEquation += str_equation[i];
	}
	for (size_t i = i_posOpen + 1; i < i_posClose; i++)
	{
		str_insideParenthesis += str_equation[i];
	}
	_itoa_s(GetSolution_Part1(str_insideParenthesis), ch_buffer, 10);
	str_newEquation += ch_buffer;
	for (size_t i = i_posClose + 1; i < str_equation.size(); i++)
	{
		str_newEquation += str_equation[i];
	}
	return GetSolution_Part1(str_newEquation);
}

long long int NewMath::GetSolutionWithoutParenthesis_Part1(std::string str_equation)
{
	long long int i_result = 0;
	size_t i_posPlus = 0;
	size_t i_posProd = 0;
	size_t i_pos = 0;
	size_t i_newPos = 0;
	std::string str_buffer = "";

	i_posPlus = str_equation.find('+', 0);
	i_posProd = str_equation.find('*', 0);

	i_pos = std::min(i_posPlus, i_posProd);

	for (size_t i = 0; i < i_pos - 1; i++)
	{
		str_buffer += str_equation[i];
	}
	i_result = stoi(str_buffer);

	while (i_pos < str_equation.size())
	{
		i_posPlus = str_equation.find('+', i_pos + 1);
		i_posProd = str_equation.find('*', i_pos + 1);

		i_newPos = std::min(i_posPlus, i_posProd);

		if (i_newPos == std::string::npos)
			i_newPos = str_equation.size() + 1;

		str_buffer.clear();
		for (size_t i = i_pos + 2; i < i_newPos - 1; i++)
			str_buffer += str_equation[i];

		if (str_equation[i_pos] == '+')
			i_result += stoi(str_buffer);
		else if (str_equation[i_pos] == '*')
			i_result *= stoi(str_buffer);

		i_pos = i_newPos;
	}

	return i_result;
}

long long int NewMath::GetSumOfSolutions_Part1()
{
	long long int i_result = 0;
	for (auto equation : v_str_equations)
	{
		i_result += GetSolution_Part1(equation);
	}
	return i_result;
}

long long int NewMath::GetSolution_Part2(std::string str_equation)
{
	size_t i_posOpen = 0, i_posClose = 0;
	std::string str_newEquation = "";
	std::string str_insideParenthesis = "";
	char ch_buffer[256];

	for (size_t i = 0; i < str_equation.size(); i++)
	{
		if (str_equation[i] == '(')
		{
			i_posOpen = i;
		}
		else if (str_equation[i] == ')')
		{
			i_posClose = i;
			break;
		}
	}

	if (i_posClose == 0)
	{
		return GetSolutionWithoutParenthesis_Part2(str_equation);
	}

	for (size_t i = 0; i < i_posOpen; i++)
	{
		str_newEquation += str_equation[i];
	}
	for (size_t i = i_posOpen + 1; i < i_posClose; i++)
	{
		str_insideParenthesis += str_equation[i];
	}
	_itoa_s(GetSolution_Part2(str_insideParenthesis), ch_buffer, 10);
	str_newEquation += ch_buffer;
	for (size_t i = i_posClose + 1; i < str_equation.size(); i++)
	{
		str_newEquation += str_equation[i];
	}
	return GetSolution_Part2(str_newEquation);
}

long long int NewMath::GetSolutionWithoutParenthesis_Part2(std::string str_equation)
{
	long long int i_result = 0;
	long long int i_inter = 0;
	size_t i_posPlus = 0;
	size_t i_newPos = 0;
	int i_posProd = 0;
	size_t i_newPosProd = 0;
	size_t i_pos = 0;
	char ch_buffer[256];

	std::string str_buffer = "";
	std::string str_newEquation = "";
	std::string str_insideplus = "";

	i_posPlus = str_equation.find('+', 0);
	i_posProd = 0;
	i_newPosProd = str_equation.find('*', i_posProd + 1);

	while (i_newPosProd < i_posPlus)
	{
		i_posProd = i_newPosProd;
		i_newPosProd = str_equation.find('*', i_posProd + 1);
	}

	if (i_posPlus == std::string::npos)
	{
		return GetSolutionWithoutParenthesisNorPlus_Part2(str_equation);
	}

	i_pos = std::min(str_equation.find('+', i_posPlus + 1), str_equation.find('*', i_posPlus + 1));
	if (i_posProd == 0)
		i_posProd = -2;
	for (int i = 0; i < i_posProd + 2; i++)
	{
		str_newEquation += str_equation[i];
	}
	for (size_t i = i_posProd + 2; i < i_posPlus - 1; i++)
	{
		str_insideplus += str_equation[i];
	}
	i_inter = stoi(str_insideplus);

	str_insideplus.clear();
	if (i_pos == std::string::npos)
		i_pos = str_equation.size() + 1;

	for (size_t i = i_posPlus + 2; i < i_pos- 1; i++)
	{
		str_insideplus += str_equation[i];
	}
	i_inter += stoi(str_insideplus);
	_itoa_s(i_inter, ch_buffer, 10);
	str_newEquation += ch_buffer;

	for (size_t i = i_pos - 1; i < str_equation.size(); i++)
	{
		str_newEquation += str_equation[i];
	}
	return GetSolutionWithoutParenthesis_Part2(str_newEquation);
}

long long int NewMath::GetSolutionWithoutParenthesisNorPlus_Part2(std::string str_equation)
{
	long long int i_result = 0;
	size_t i_posProd = 0;
	size_t i_newPos = 0;
	std::string str_buffer = "";

	i_posProd = str_equation.find('*', 0);

	if (i_posProd == std::string::npos)
		i_posProd = str_equation.size() + 1;

	for (size_t i = 0; i < i_posProd - 1; i++)
	{
		str_buffer += str_equation[i];
	}
	i_result = stoi(str_buffer);

	while (i_posProd < str_equation.size())
	{
		i_newPos = str_equation.find('*', i_posProd + 1);

		if (i_newPos == std::string::npos)
			i_newPos = str_equation.size() + 1;

		str_buffer.clear();
		for (size_t i = i_posProd + 2; i < i_newPos - 1; i++)
			str_buffer += str_equation[i];
		
		i_result *= stoi(str_buffer);

		i_posProd = i_newPos;
	}

	return i_result;
}

long long int NewMath::GetSumOfSolutions_Part2()
{
	long long int i_result = 0;
	for (auto equation : v_str_equations)
	{
		i_result += GetSolution_Part2(equation);
	}
	return i_result;
}