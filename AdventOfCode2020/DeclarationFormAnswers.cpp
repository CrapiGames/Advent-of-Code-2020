#include "DeclarationFormAnswers.h"




void DeclarationFormAnswers::Init(std::string str_filepath)
{
	std::fstream file_declarationFormAnswers;
	char ch_buffer[1000];
	char delim = '\n';
	std::string str_groupAnswers;
	file_declarationFormAnswers.open(str_filepath);


	while (!file_declarationFormAnswers.eof())
	{
		file_declarationFormAnswers.getline(ch_buffer, 1000, delim);
		str_groupAnswers = ch_buffer;
		while (!file_declarationFormAnswers.eof() && delim != file_declarationFormAnswers.peek())
		{
			file_declarationFormAnswers.getline(ch_buffer, 1000, delim);
			str_groupAnswers += delim;
			str_groupAnswers += ch_buffer;
		}
		file_declarationFormAnswers.ignore();
		DeclarationFormAnswers::AddGroupAnswers(str_groupAnswers);
	}

}

int DeclarationFormAnswers::GetTheSumOfCounts_Anyone()
{
	int i_count = 0;
	for (auto& groupAnswers : v_everyGroupAnswers)
	{
		i_count += groupAnswers->GetCollectedAnswers_Anyone().size();
	}
	return i_count;
}

int DeclarationFormAnswers::GetTheSumOfCounts_Everyone()
{
	int i_count = 0;
	for (auto& groupAnswers : v_everyGroupAnswers)
	{
		i_count += groupAnswers->GetCollectedAnswers_Everyone().size();
	}
	return i_count;
}

void DeclarationFormAnswers::AddGroupAnswers(std::string str_GroupAnswers)
{
	GroupAnswers *groupAnswers;
	groupAnswers = new GroupAnswers();

	groupAnswers->Init(str_GroupAnswers);
	v_everyGroupAnswers.push_back(groupAnswers);
}

void GroupAnswers::Init(std::string str_groupAnswers)
{
	size_t i_pos[2] = { 0,0 };
	std::string str_answers;

	while (i_pos[0] < str_groupAnswers.size())
	{
		i_pos[1] = str_groupAnswers.find('\n', i_pos[0] + 1);
		if (i_pos[1] == std::string::npos)
			i_pos[1] = str_groupAnswers.size();
		
		if (i_pos[0] == 0)
			str_answers = str_groupAnswers[0];
		else
			str_answers = "";

		for (size_t i = i_pos[0] + 1; i < i_pos[1]; i++)
			str_answers += str_groupAnswers[i];

		v_str_personAnswers.push_back(str_answers);
		i_pos[0] = i_pos[1];
	}

}

std::string GroupAnswers::GetCollectedAnswers_Anyone()
{
	std::string str_CollectedAnswers = "";
	bool is_Missing;

	for (auto& str_personAnswers : v_str_personAnswers)
	{
		for (size_t i = 0; i < str_personAnswers.size(); i++)
		{
			is_Missing = true;
			for (size_t j = 0; j < str_CollectedAnswers.size(); j++)
			{
				is_Missing = is_Missing && !CompareStrings(str_personAnswers, i, 1, str_CollectedAnswers, j, 1);
			}

			if (is_Missing)
				str_CollectedAnswers += str_personAnswers[i];
		}
	}

	return str_CollectedAnswers;
}

std::string GroupAnswers::GetCollectedAnswers_Everyone()
{
	std::string str_CollectedAnswers_Anyone = GetCollectedAnswers_Anyone();
	std::string str_CollectedAnswers = "";
	bool is_Everywhere;
	bool is_MissingFromPerson;

	for (size_t i = 0; i < str_CollectedAnswers_Anyone.size(); i++)
	{
		is_Everywhere = true;
		for (auto& str_personAnswers : v_str_personAnswers)
		{
			is_MissingFromPerson = true;
			for (size_t j = 0; j < str_personAnswers.size(); j++)
			{
				is_MissingFromPerson = is_MissingFromPerson && !CompareStrings(str_CollectedAnswers_Anyone, i, 1, str_personAnswers, j, 1);
			}

			is_Everywhere = is_Everywhere && !is_MissingFromPerson;
		}
		if (is_Everywhere)
			str_CollectedAnswers += str_CollectedAnswers_Anyone[i];
	}

	return str_CollectedAnswers;
}
