#include "MonsterMessage.h"

void MonsterMessages::Init(std::string str_filepath)
{
	std::fstream file_rulesAndMessages;
	char ch_buffer[1000];
	std::string str_key, str_rule;
	std::deque<char> dq_c_message;

	file_rulesAndMessages.open(str_filepath);
	while (!(file_rulesAndMessages.peek() == '\n'))
	{
		file_rulesAndMessages.getline(ch_buffer, 1000, ':');
		str_key = ch_buffer;
		file_rulesAndMessages.ignore();
		file_rulesAndMessages.getline(ch_buffer, 1000);
		str_rule = ch_buffer;
		m_str_rules.emplace( str_key, str_rule);
	}

	file_rulesAndMessages.ignore();

	while (!file_rulesAndMessages.eof())
	{
		file_rulesAndMessages.getline(ch_buffer, 1000);
		str_rule = ch_buffer;
		dq_c_message.clear();
		for (size_t i = 0; i < str_rule.size(); i++)
			dq_c_message.push_back(str_rule[i]);
		v_dq_c_messages.push_back(dq_c_message);
	}

}

bool MonsterMessages::IsMatchingRule(std::string str_ruleKey, std::deque<char> *dq_c_message)
{
	std::string str_ruleToFollow = m_str_rules[str_ruleKey];
	int i_posSpace, i_newPosSpace, i_posOr;
	std::string str_newRule;
	std::deque<char> dq_c_message_bis = *dq_c_message;
	bool isOK;

	if (dq_c_message->empty())
		return false;

	if (str_ruleToFollow[0] == '"')
	{
		if (dq_c_message->at(0) == str_ruleToFollow[1])
		{
			dq_c_message->pop_front();
			return true;
		}
		else
			return false;
	}

	i_posSpace = -1;
	i_posOr = str_ruleToFollow.find('|', 0);


	if (i_posOr == std::string::npos)
	{
		while (i_posSpace < (int)str_ruleToFollow.size())
		{
			i_newPosSpace = str_ruleToFollow.find(' ', i_posSpace + 1);
			if (i_newPosSpace == std::string::npos)
				i_newPosSpace = str_ruleToFollow.size();

			str_newRule.clear();
			for (int i = i_posSpace + 1; i < i_newPosSpace; i++)
				str_newRule += str_ruleToFollow[i];

			if (!IsMatchingRule(str_newRule, dq_c_message))
				return false;

			i_posSpace = i_newPosSpace;
		}
		return true;
	}
	else
	{
		str_newRule.clear();
		for (int i = 0; i < i_posOr - 1; i++)
			str_newRule += str_ruleToFollow[i];

		isOK = true;
		while (i_posSpace < i_posOr - 1)
		{
			i_newPosSpace = str_ruleToFollow.find(' ', i_posSpace + 1);
			if (i_newPosSpace == std::string::npos)
				i_newPosSpace = str_ruleToFollow.size();

			str_newRule.clear();
			for (int i = i_posSpace + 1; i < i_newPosSpace; i++)
				str_newRule += str_ruleToFollow[i];

			if (!IsMatchingRule(str_newRule, &dq_c_message_bis))
			{
				isOK = false;
				break;
			}

			i_posSpace = i_newPosSpace;
		}

		if (isOK)
		{
			*dq_c_message = dq_c_message_bis;
			return true;
		}
		else 
		{
			i_posSpace = i_posOr + 1;
			while (i_posSpace < (int)str_ruleToFollow.size())
			{
				i_newPosSpace = str_ruleToFollow.find(' ', i_posSpace + 1);
				if (i_newPosSpace == std::string::npos)
					i_newPosSpace = str_ruleToFollow.size();

				str_newRule.clear();
				for (int i = i_posSpace + 1; i < i_newPosSpace; i++)
					str_newRule += str_ruleToFollow[i];

				if (!IsMatchingRule(str_newRule, dq_c_message))
					return false;

				i_posSpace = i_newPosSpace;
			}

			return true;
		}
	}


}

int MonsterMessages::GetNumberOfMessagesMatchingRule0()
{
	int i_count = 0;

	for (auto dq_c_message : v_dq_c_messages)
	{
		if (IsMatchingRule("0", &dq_c_message) && dq_c_message.empty())
			i_count++;
	}

	return i_count;
}


int MonsterMessages::GetNumberOfMessagesMatchingRule0_Loop()
{
	int i_count = 0;
	int i_count42Possibilities = 0;
	std::deque<char> dq_c_message_bis;
	std::deque<char> dq_c_message_ter;
	bool isOk;

	for (auto dq_c_message : v_dq_c_messages)
	{
		dq_c_message_bis = dq_c_message;
		while (IsMatchingRule("42", &dq_c_message_bis))
		{
			i_count42Possibilities++;
		}

		for (int i_numberOf8 = 1; i_numberOf8 <= i_count42Possibilities; i_numberOf8++)
		{
			for (int i_numberOf11 = 1; i_numberOf11 <= i_count42Possibilities - i_numberOf8; i_numberOf11++)
			{
				dq_c_message_bis = dq_c_message;

				for (int i = 0; i < i_numberOf8 + i_numberOf11; i++)
					IsMatchingRule("42", &dq_c_message_bis);

				isOk = true;
				for (int i = 0; i < i_numberOf11; i++)
				{
					isOk = isOk && IsMatchingRule("31", &dq_c_message_bis);
					if (!isOk)
						break;
				}

				if (isOk && dq_c_message_bis.empty())
					break;

			}

			if (isOk && dq_c_message_bis.empty())
			{
				i_count++;
				break;
			}
		}

	}

	return i_count;
}