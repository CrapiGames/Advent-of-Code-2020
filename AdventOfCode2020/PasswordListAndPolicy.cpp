#include "PasswordListAndPolicy.h"

int PasswordList::GetNumberOfValidPasswords_Part1()
{
	int count = 0;

	for (auto& passWithPol : v_str_passwords)
	{
		if (passWithPol->checkIntegrity_Part1())
			count++;
	}

	return count;
}

int PasswordList::GetNumberOfValidPasswords_Part2()
{
	int count = 0;

	for (auto& passWithPol : v_str_passwords)
	{
		if (passWithPol->checkIntegrity_Part2())
			count++;
	}

	return count;
}


void PasswordList::Init(std::string str_filepath)
{
	int i_rangeMin;
	int i_rangeMax;
	std::string str_polch;
	std::string str_pass;
	char ch_buffer[256];
	std::fstream passwordListFile;

	passwordListFile.open(str_filepath);

	while (!passwordListFile.eof())
	{
		passwordListFile.getline(ch_buffer, 256, '-');
		i_rangeMin = atoi(ch_buffer);

		passwordListFile.getline(ch_buffer, 256, ' ');
		i_rangeMax = atoi(ch_buffer);

		passwordListFile.getline(ch_buffer, 256, ':');
		str_polch = ch_buffer;

		passwordListFile.ignore();
		passwordListFile.getline(ch_buffer, 256, '\n');
		str_pass = ch_buffer;

		AddPassword(i_rangeMin, i_rangeMax, str_polch, str_pass);
	}
}

void PasswordList::AddPassword(int i_rangeMin, int i_rangeMax, std::string str_polch, std::string str_pass)
{
	PasswordWithPolicy *passwordToAdd;
	passwordToAdd = new PasswordWithPolicy(i_rangeMin, i_rangeMax, str_polch, str_pass);
	v_str_passwords.push_back(passwordToAdd);
}

bool PasswordWithPolicy::checkIntegrity_Part1()
{
	int count = 0;
	size_t pos = 0;
	
	pos = str_password.find(str_policyChar);

	while (pos != std::string::npos)
	{
		pos = str_password.find(str_policyChar, pos+1);
		count++;
	}

	if (CompareValueInRangeIncluded(count, i_policyRangeMin, i_policyRangeMax))
		return true;
	else
		return false;

}

bool PasswordWithPolicy::checkIntegrity_Part2()
{
	bool testMin = CompareStrings(str_password, i_policyRangeMin - 1, 1, str_policyChar);
	bool testMax = CompareStrings(str_password, i_policyRangeMax - 1, 1, str_policyChar);

	if (testMin && !testMax)
		return true;
	else if (!testMin && testMax)
		return true;
	else
		return false;

}