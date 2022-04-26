#include "ExpenseReport.h"


void ExpenseReport::Init(std::string str_filePath)
{
	char ch_expense[256];
	int i_count = 0;
	std::fstream file_expenseReport;
	file_expenseReport.open(str_filePath);

	while (!file_expenseReport.eof())
	{
		file_expenseReport.getline(ch_expense, 256);
		i_expenses[i_count] = atoi(ch_expense);
		i_count++;
	}

	i_sizeOfTheReport = i_count;
}

int ExpenseReport::CheckIntegrityReport_2()
{
	for (int i = 0; i < i_sizeOfTheReport; i++)
	{
		for (int j = i + 1; j < i_sizeOfTheReport; j++)
		{
			if (IsExisting(2020 - i_expenses[i] - i_expenses[j]))
			{
				return i_expenses[i] * i_expenses[j] * i_expenses[ExpenseReport::FindExistingNumber(2020 - i_expenses[i] - i_expenses[j])];
			}
		}
	}

	std::cout << "ExpenseReport::CheckIntegrityReport_2 : No answer found !!" << std::endl;
	return -1;
}
int ExpenseReport::CheckIntegrityReport_1()
{
	for (int i = 0; i < i_sizeOfTheReport; i++)
	{
		if (IsExisting(2020 - i_expenses[i]))
		{
			return i_expenses[i] * i_expenses[ExpenseReport::FindExistingNumber(2020 - i_expenses[i])];
		}
	}

	std::cout << "ExpenseReport::CheckIntegrityReport_1 : No answer found !!" << std::endl;
	return -1;
}

int ExpenseReport::FindExistingNumber(int i_numberToFind)
{
	for (int i = 0; i < i_sizeOfTheReport; i++)
	{
		if (i_expenses[i] == i_numberToFind)
			return i;
	}

	std::cout << "ExpenseReport::FindExistingNumber : No existing number found !!" << std::endl;
	return -1;
}

bool ExpenseReport::IsExisting(int i_numberToFind)
{
	for (int i = 0; i < i_sizeOfTheReport; i++)
	{
		if (i_expenses[i] == i_numberToFind)
			return true;
	}

	return false;
}