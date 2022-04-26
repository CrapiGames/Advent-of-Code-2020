#pragma once
#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Utility.h"

class BoardingPass;
class BoardingPasses;

class BoardingPasses
{
public:
	std::vector<BoardingPass*> v_boardingPasses;

	void Init(std::string str_filepath);
	int GetHighestID();
	bool IsExisting(int i_seatId);
	int GetTheSeatID();
};

class BoardingPass
{
public:
	std::string str_seatPartition;
	int i_row;
	int i_column;

	void Init(std::string str_seatPart);
	int GetSeatID();

};