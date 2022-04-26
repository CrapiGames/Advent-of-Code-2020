#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "Utility.h"

class SeatLayout
{
public:
	std::vector<std::string> v_seatLayout;

	void Init(std::string str_filepath);
	void Init(std::vector<std::string> v_SseatLayout);
	bool Is_aSeat(int i_row, int i_column);
	bool Is_Occupied(int i_row, int i_column);
	int getNumberOfOccupiedAdjacentSeats(int i_row, int i_column);
	int getNumberOfOccupiedApparentSeats(int i_row, int i_column);
	bool applyRules_Part1();
	bool applyRules_Part2();
	int getTheNumberOfOccupiedSeatsAtTheEnd_Part1();
	int getTheNumberOfOccupiedSeatsAtTheEnd_Part2();
};
