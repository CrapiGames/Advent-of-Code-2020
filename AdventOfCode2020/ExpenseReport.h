#pragma once

#include <fstream>
#include <iostream>

class ExpenseReport
{
public:
	//ExpenseReport();
	int i_sizeOfTheReport;
	int i_expenses[10000];

	void Init(std::string str_filePath);

	int CheckIntegrityReport_1();
	int CheckIntegrityReport_2();

	int FindExistingNumber(int i_numberToFind);
	bool IsExisting(int i_numberToFind);

};