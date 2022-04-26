#include "TicketTrain.h"


void TrainTickets::Init(std::string str_filepath)
{
	std::fstream file_tickets;
	char ch_buffer[1000];
	std::string str_line;
	std::vector<int> i_values;
	Ticket *ticket;

	m_str_i_fieldRules.clear();
	v_otherTickets.clear();

	file_tickets.open(str_filepath);

	while (file_tickets.peek() != '\n')
	{
		i_values.clear();
		file_tickets.getline(ch_buffer, 1000, ':');
		str_line = ch_buffer;
		file_tickets.ignore();
		file_tickets.getline(ch_buffer, 1000, '-');
		i_values.push_back( atoi(ch_buffer));
		file_tickets.getline(ch_buffer, 1000, ' ');
		i_values.push_back(atoi(ch_buffer));
		file_tickets.getline(ch_buffer, 1000, ' ');
		file_tickets.getline(ch_buffer, 1000, '-');
		i_values.push_back(atoi(ch_buffer));
		file_tickets.getline(ch_buffer, 1000);
		i_values.push_back(atoi(ch_buffer));

		m_str_i_fieldRules.insert({ str_line, i_values });
	}

	file_tickets.ignore();
	file_tickets.getline(ch_buffer, 1000);
	file_tickets.getline(ch_buffer, 1000);
	str_line = ch_buffer;

	ticket = new Ticket();
	ticket->Init(str_line);
	myTicket = ticket;

	file_tickets.ignore();
	file_tickets.getline(ch_buffer, 1000);

	while (!file_tickets.eof())
	{
		file_tickets.getline(ch_buffer, 1000);
		str_line = ch_buffer;
		ticket = new Ticket();
		ticket->Init(str_line);
		v_otherTickets.push_back(ticket);
	}

}

int TrainTickets::GetSumOfInvalid(Ticket ticket) 
{
	int i_result = 0;
	bool isToAdd;

	for (auto i_value : ticket.v_i_fieldsValue)
	{
		isToAdd = true;
		for (auto i_rangeFields : m_str_i_fieldRules)
		{
			if ((i_value >= i_rangeFields.second[0] && i_value <= i_rangeFields.second[1]) || (i_value >= i_rangeFields.second[2] && i_value <= i_rangeFields.second[3]))
			{
				isToAdd = false;
				break;
			}
		}
		if (isToAdd)
			i_result += i_value;
	}
	return i_result;
}

int TrainTickets::GetSumOfAllInvalid()
{
	int i_result = 0;
	for (auto ticket : v_otherTickets)
	{
		i_result += GetSumOfInvalid(*ticket);
	}
	return i_result;
}


void TrainTickets::ClearInvalidTickets()
{
	bool isFound = true;
	while (isFound)
	{
		isFound = false;
		for (auto itr = v_otherTickets.begin(); itr != v_otherTickets.end(); ++itr)
		{
			if (GetSumOfInvalid(**itr) > 0)
			{
				v_otherTickets.erase(itr);
				isFound = true;
				break;
			}
		}
	}
}

void Ticket::Init(std::string str_line)
{
	int i_pos = -1;
	int i_last = -1;
	std::string str_number;

	while (i_pos < (int)str_line.size())
	{
		i_last = i_pos;
		i_pos = str_line.find(',', i_pos + 1);
		if (i_pos == std::string::npos)
			i_pos = str_line.size();
		str_number.clear();
		for (int i = i_last + 1; i < i_pos; i++)
		{
			str_number += str_line[i];
		}
		v_i_fieldsValue.push_back(stoi(str_number));
	}
}

int TrainTickets::GetFieldValidated(int i1, int i2, int i3, int i4)
{
	int i_result = -1;
	bool isValidated = false;
	bool hasToBeDone = true;
	int i_count = 0;

	for (size_t i_fieldId = 0; i_fieldId < myTicket->v_i_fieldsValue.size(); i_fieldId++)
	{
		isValidated = true;
		hasToBeDone = true;
		for (auto field : m_str_i_fieldRules)
		{
			if (field.second[4] == i_fieldId)
				hasToBeDone = false;
		}

		if (hasToBeDone)
		{
			for (auto ticket : v_otherTickets)
			{
				if ((ticket->v_i_fieldsValue[i_fieldId] <i1 || ticket->v_i_fieldsValue[i_fieldId] > i2) && (ticket->v_i_fieldsValue[i_fieldId] <i3 || ticket->v_i_fieldsValue[i_fieldId] > i4))
				{
					isValidated = false;
					break;
				}
			}

			if (isValidated)
			{
				i_count++;
				i_result = i_fieldId;
			}
		}
	}

	if (i_count == 1)
		return i_result;
	else
		return -1;
}




long long int TrainTickets::GetTheProduceOfDepartureFields()
{
	long long int i_result = 1;
	bool hasToContinue = true;

	ClearInvalidTickets();

	for (auto& field : m_str_i_fieldRules)
	{
		field.second.push_back(-1);
	}

	while (hasToContinue)
	{
		for (auto& field : m_str_i_fieldRules)
		{
			if (field.second[4] == -1)
			{
				field.second[4] = GetFieldValidated(field.second[0], field.second[1], field.second[2], field.second[3]);
			}
		}

		hasToContinue = false;
		for (auto field : m_str_i_fieldRules)
		{
			if (CompareStrings(field.first, 0, 9, "departure") && field.second[4] == -1)
				hasToContinue = true;
		}
	}

	for (auto field : m_str_i_fieldRules)
	{
		if (CompareStrings(field.first, 0, 9, "departure"))
			i_result *= myTicket->v_i_fieldsValue[field.second[4]];
	}

	return i_result;
}