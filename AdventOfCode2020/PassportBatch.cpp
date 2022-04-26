#include "PassportBatch.h"

constexpr auto IDLENGTH = 3;

const std::string str_IdRef[NB_ID] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid" };

void PassportBatch::Init(std::string str_passportBatchFilePath)
{
	std::fstream passportBatchFile;
	char ch_buffer[256];
	char delim = '\n';
	std::string str_passportFullInfo;

	passportBatchFile.open(str_passportBatchFilePath);

	while (!passportBatchFile.eof())
	{
		passportBatchFile.getline(ch_buffer, 256, delim);
		str_passportFullInfo = ch_buffer;
		while(!passportBatchFile.eof() && delim != passportBatchFile.peek())
		{
			passportBatchFile.getline(ch_buffer, 256, delim);
			str_passportFullInfo += delim;
			str_passportFullInfo += ch_buffer;
		}
		PassportBatch::AddPassport(str_passportFullInfo);
	}

}

int PassportBatch::CountAllValidPassportsWithoutICD_Part1()
{
	int i_count = 0;
	for (auto& passport : passportList)
	{
		if (passport->CheckIntegrityButCID_Part1())
			i_count++;
	}
	return i_count;
}

int PassportBatch::CountAllValidPassportsWithoutICD_Part2()
{
	int i_count = 0;
	for (auto& passport : passportList)
	{
		if (passport->CheckIntegrityButCID_Part2())
			i_count++;
	}
	return i_count;
}

void PassportBatch::AddPassport(std::string str_passportFullInfo) 
{
	Passport *pass = new Passport();
	pass->Init(str_passportFullInfo);
	passportList.push_back(pass);
}

void Passport::Init(std::string str_passportFullInfo)
{
	size_t i_pos[2] = { 0,0 };
	bool is_dataFound = false;

	std::string str_separator = ":";
	std::string str_fieldID;
	std::string str_fieldInfo;

	i_pos[0] = str_passportFullInfo.find(str_separator, 0);

	for (int i = 0; i < NB_ID; i++)
		str_fields[i] = "";

	while (i_pos[0] < str_passportFullInfo.size())
	{
		i_pos[1] = str_passportFullInfo.find(str_separator, i_pos[0] + 1);
		if (i_pos[1] == std::string::npos)
			i_pos[1] = str_passportFullInfo.size() + IDLENGTH + 1;
		
		str_fieldID = "";
		for (size_t i = i_pos[0] - IDLENGTH; i < i_pos[0]; i++)
			str_fieldID += str_passportFullInfo[i];

		str_fieldInfo = "";
		for (size_t i = i_pos[0] + 1; i < i_pos[1] - IDLENGTH - 1; i++)
			str_fieldInfo += str_passportFullInfo[i];
			
		Passport::FillFieldId(str_fieldID, str_fieldInfo);
		
		i_pos[0] = i_pos[1];
	}

}

void Passport::FillFieldId(std::string str_fieldID, std::string str_fieldInfo)
{
	for (int i = 0; i < NB_ID; i++)
	{
		if (CompareStrings(str_fieldID, str_IdRef[i]))
			str_fields[i] = str_fieldInfo;
	}

}

bool Passport::CheckIntegrityButCID_Part1()
{
	for (int i = 0; i < NB_ID; i++)
	{
		if (str_fields[i].empty() && i != ID_CID)
			return false;
	}
	return true;
}

bool Passport::CheckIntegrityButCID_Part2()
{
	for (int i = 0; i < NB_ID; i++)
	{
		if (!Passport::CheckIntegrityCriteria(i))
			return false;
	}
	return true;
}

bool Passport::CheckIntegrityCriteria(int fieldID)
{
	int i_value;
	std::string str_value;
	bool is_buffer;
	bool is_OK = true;;
	int i_range[2];

	const char HCL_RANGE[17] = "0123456789abcdef";
	const std::string ECL_RANGE[7] = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
	const char PID_RANGE[11] = "0123456789";

	str_value = str_fields[fieldID];

	if (str_value.empty() && fieldID != ID_CID)
		return false;

	switch (fieldID)
	{
	case ID_BYR:
		i_range[0] = 1920; i_range[1] = 2002;
		break;

	case ID_IYR:
		i_range[0] = 2010; i_range[1] = 2020;
		break;

	case ID_EYR:
		i_range[0] = 2020; i_range[1] = 2030;
		break;

	case ID_HGT:
		str_value = GetACopy(str_fields[ID_HGT], str_fields[ID_HGT].size() - 2, 2);
		if (CompareStrings(str_value, "cm"))
		{	i_range[0] = 150; i_range[1] = 193;		}
		else if (CompareStrings(str_value, "in"))
		{	i_range[0] = 59; i_range[1] = 76;		}
		else
		{	i_range[0] = 1; i_range[1] = 0;			}
		str_value = GetACopy(str_fields[ID_HGT], 0, str_fields[ID_HGT].size() - 2);
		break;

	case ID_HCL:
		is_OK = CompareStrings(str_value, 0, 1, "#") && str_value.size() == 7;
		break;

	case ID_ECL:
		is_OK = str_value.size() == 3;
		break;

	case ID_PID:
		is_OK = str_value.size() == 9;
		break;
	}

	if (!is_OK)
		return false;

	switch (fieldID)
	{
	case ID_BYR:
	case ID_IYR:
	case ID_EYR:
	case ID_HGT:
		i_value = stoi(str_value);
		is_OK = CompareValueInRangeIncluded(i_value, i_range[0], i_range[1]);
		break;

	case ID_HCL:
		for (size_t i = 1; i < str_value.size(); i++)
		{
			is_buffer = false;
			for (int j = 0; j < 16; j++)
				is_buffer = is_buffer || CompareStrings(str_value, i, 1, HCL_RANGE, j, 1);
			is_OK = is_OK && is_buffer;
		}
		break;

	case ID_ECL:
		is_OK = false;
		for (int j = 0; j < 7; j++)
			is_OK = is_OK || CompareStrings(str_value, 0, 3, ECL_RANGE[j]);
		break;

	case ID_PID:
		for (size_t i = 0; i < str_value.size(); i++)
		{
			is_buffer = false;
			for (int j = 0; j < 10; j++)
				is_buffer = is_buffer || CompareStrings(str_value, i, 1, PID_RANGE, j, 1);
			is_OK = is_OK && is_buffer;
		}
		break;

	case ID_CID:
		is_OK = true;
		break;

	default:
		is_OK = false;
		break;
	}

	return is_OK;
}