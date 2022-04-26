#pragma once
#include <fstream>
#include <string>
#include <vector>

class BusSevices
{
public:
	int i_timestampDeparture;
	std::vector<int> v_i_BusIds;

	void Init(std::string str_filepath);
	int GetTheEarliestBusIdByWaitingMinutes();
	long long GetTheEarliestSubsequentDeparture();
};