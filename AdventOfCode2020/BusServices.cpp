#include "BusServices.h"


void BusSevices::Init(std::string str_filepath)
{
	std::fstream file_services;
	char ch_buffer[256];
	int i_buffer;
	
	file_services.open(str_filepath);

	file_services.getline(ch_buffer, 256);
	i_timestampDeparture = atoi(ch_buffer);

	while (!file_services.eof())
	{
		file_services.getline(ch_buffer, 256, ',');
		if (ch_buffer[0] == 'x')
			i_buffer = -1;
		else
			i_buffer = atoi(ch_buffer);

		v_i_BusIds.push_back(i_buffer);
	}
}

int BusSevices::GetTheEarliestBusIdByWaitingMinutes()
{
	int i_posBestBus = -1;
	int i_timeToWait = 0;

	for (size_t i = 0; i < v_i_BusIds.size(); i++)
	{
		if (v_i_BusIds[i] != -1)
		{
			i_timeToWait = v_i_BusIds[i] * (static_cast<int>(i_timestampDeparture / v_i_BusIds[i]) + 1 ) - i_timestampDeparture;
			if (i_posBestBus == -1)
				i_posBestBus = i;
			else if (i_timeToWait < v_i_BusIds[i_posBestBus] * (static_cast<int>(i_timestampDeparture / v_i_BusIds[i_posBestBus]) + 1) - i_timestampDeparture)
				i_posBestBus = i;

		}
	}

	return v_i_BusIds[i_posBestBus] * (v_i_BusIds[i_posBestBus] * (static_cast<int>(i_timestampDeparture / v_i_BusIds[i_posBestBus]) + 1) - i_timestampDeparture);
}

long long BusSevices::GetTheEarliestSubsequentDeparture()
{
	long long i_Bus0Departure = 0;
	bool is_Found = false;
	std::vector<size_t> v_i_posExists;
	long long i_deltaOpti;

	for (size_t i = 0; i < v_i_BusIds.size(); i++)
	{
		if (v_i_BusIds[i] != -1)
		{
			v_i_posExists.push_back(i);
		}
	}

	i_deltaOpti = 1;
	for (size_t i = 1; i < v_i_posExists.size(); i++)
	{
		i_deltaOpti *= v_i_BusIds[v_i_posExists[i - 1]];
		is_Found = false;

		while (!is_Found)
		{
			is_Found = true;
			i_Bus0Departure += i_deltaOpti;

			if (static_cast<long long>((v_i_posExists[i] + i_Bus0Departure) / v_i_BusIds[v_i_posExists[i]]) * v_i_BusIds[v_i_posExists[i]] != v_i_posExists[i] + i_Bus0Departure)
			{
				is_Found = false;
			}
		}
	}

	return i_Bus0Departure;


	/*
	while (!is_Found)
	{
		i_Bus0Departure += v_i_BusIds[0];
		is_Found = true;

		if (static_cast<int>((i_posMax + i_Bus0Departure) / v_i_BusIds[i_posMax]) * v_i_BusIds[i_posMax] != i_posMax + i_Bus0Departure)
		{
			is_Found = false;
		}
	}


	is_Found = false;
	i_deltaOpti = v_i_BusIds[0] * v_i_BusIds[i_posMax];

	while (!is_Found)
	{
		i_Bus0Departure += i_deltaOpti;
		is_Found = true;

		for (size_t i = 0; i < v_i_posExists.size(); i++)
		{
			if (v_i_BusIds[v_i_posExists[i]] == -1)
				;
			else
			{
				if (static_cast<int>((v_i_posExists[i] + i_Bus0Departure) / v_i_BusIds[v_i_posExists[i]]) * v_i_BusIds[v_i_posExists[i]] != v_i_posExists[i] + i_Bus0Departure)
				{
					is_Found = false;
					break;
				}
			}
		}


	}
	*/
	return i_Bus0Departure;
}