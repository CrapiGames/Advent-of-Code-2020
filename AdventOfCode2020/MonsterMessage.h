#pragma once
#include <fstream>
#include <string>
#include <unordered_map>
#include <deque>
#include <vector>

struct MonsterMessages
{
	std::unordered_map<std::string, std::string> m_str_rules;
	std::vector<std::deque<char>> v_dq_c_messages;

	void Init(std::string str_filepath);
	bool IsMatchingRule(std::string str_ruleKey, std::deque<char> *dq_c_message);
	int GetNumberOfMessagesMatchingRule0();
	int GetNumberOfMessagesMatchingRule0_Loop();
};