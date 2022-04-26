#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Utility.h"

class Ticket;
class TrainTickets;

class TrainTickets
{
public:
	std::map<std::string, std::vector<int>> m_str_i_fieldRules;
	Ticket *myTicket;
	std::vector<Ticket*> v_otherTickets;

	void Init(std::string str_filepath);
	int GetSumOfInvalid(Ticket ticket);
	int GetSumOfAllInvalid();
	void ClearInvalidTickets();

	long long int GetTheProduceOfDepartureFields();
	int GetFieldValidated(int i1, int i2, int i3, int i4);
};

class Ticket
{
public:
	std::vector<int> v_i_fieldsValue;

	void Init(std::string str_line);
};