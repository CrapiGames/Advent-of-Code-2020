#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Utility.h"

class PasswordWithPolicy;
class PasswordList;

class PasswordList
{
public:
	std::vector<PasswordWithPolicy*> v_str_passwords;

	int GetNumberOfValidPasswords_Part1();
	int GetNumberOfValidPasswords_Part2();
	void Init(std::string str_filepath);

	void AddPassword(int i_rangeMin, int i_rangeMax, std::string str_polch, std::string str_pass);
};

class PasswordWithPolicy
{
public:
	int i_policyRangeMin;
	int i_policyRangeMax;
	std::string str_policyChar;
	std::string str_password;

	PasswordWithPolicy(int i_rangeMin, int i_rangeMax, std::string str_polch, std::string str_pass) : i_policyRangeMin(i_rangeMin), i_policyRangeMax(i_rangeMax), str_policyChar(str_polch), str_password(str_pass) {}
	bool checkIntegrity_Part1();
	bool checkIntegrity_Part2();
};