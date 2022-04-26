#pragma once
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Utility.h"

enum passportField
{
	ID_BYR = 0,
	ID_IYR,
	ID_EYR,
	ID_HGT,
	ID_HCL,
	ID_ECL,
	ID_PID, 
	ID_CID,
	NB_ID
};

class PassportBatch;
class Passport;

class PassportBatch
{
public:
	std::vector<Passport*> passportList;

	void Init(std::string str_passportBatchFilePath);
	int CountAllValidPassportsWithoutICD_Part1();
	int CountAllValidPassportsWithoutICD_Part2();
	void AddPassport(std::string str_passportFullInfo);
};

class Passport
{
public:
	std::string str_fields[NB_ID];

	void Init(std::string str_passportFullInfo);
	void FillFieldId(std::string str_fieldID, std::string str_fieldInfo);
	bool CheckIntegrityButCID_Part1();
	bool CheckIntegrityButCID_Part2();
	bool CheckIntegrityCriteria(int fieldID);

};