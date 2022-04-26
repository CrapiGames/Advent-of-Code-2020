#include "SeatLayout.h"

void SeatLayout::Init(std::string str_filepath)
{
	std::fstream file_seatLayout;
	char ch_buffer[256];
	std::string str_row;
	file_seatLayout.open(str_filepath);
	v_seatLayout.clear();

	while (!file_seatLayout.eof())
	{
		file_seatLayout.getline(ch_buffer, 256);
		str_row = ch_buffer;
		v_seatLayout.push_back(str_row);
	}
}

void SeatLayout::Init(std::vector<std::string> v_SseatLayout)
{
	v_seatLayout.clear();
	for (size_t i = 0; i < v_SseatLayout.size(); i++)
	{
		v_seatLayout.push_back(v_SseatLayout[i]);
	}
}

bool SeatLayout::Is_aSeat(int i_row, int i_column)
{
	return CompareStrings(v_seatLayout[i_row], i_column, 1, "L") || CompareStrings(v_seatLayout[i_row], i_column, 1, "#");
}

bool SeatLayout::Is_Occupied(int i_row, int i_column)
{
	return CompareStrings(v_seatLayout[i_row], i_column, 1, "#");
}

int SeatLayout::getNumberOfOccupiedAdjacentSeats(int i_row, int i_column)
{
	int i_count = 0;

	for (int i_diffRow = -1; i_diffRow < 2; i_diffRow++)
	{
		for (int i_diffColumn = -1; i_diffColumn < 2; i_diffColumn++)
		{
			if (i_row + i_diffRow > -1 && i_row + i_diffRow < v_seatLayout.size()
				&& i_column + i_diffColumn > -1 && i_column + i_diffColumn < v_seatLayout[i_row].size() )
			{
				if (i_diffRow == 0 && i_diffColumn == 0)
					;
				else
				{
					if (Is_Occupied(i_row + i_diffRow, i_column + i_diffColumn))
						i_count++;
				}
			}
		}
	}

	return i_count;
}

int SeatLayout::getNumberOfOccupiedApparentSeats(int i_row, int i_column)
{
	int i_count = 0;
	int i_try = 0;
	bool hasToGoNext = false;

	for (int i_diffRow = -1; i_diffRow < 2; i_diffRow++)
	{
		for (int i_diffColumn = -1; i_diffColumn < 2; i_diffColumn++)
		{
			i_try = 1;
			hasToGoNext = false;

			while (!hasToGoNext)
			{
				if (i_row + i_diffRow * i_try > -1 && i_row + i_diffRow * i_try < v_seatLayout.size()
					&& i_column + i_diffColumn * i_try > -1 && i_column + i_diffColumn * i_try < v_seatLayout[i_row].size())
				{
					if (i_diffRow == 0 && i_diffColumn == 0)
						hasToGoNext = true;
					else
					{
						if (Is_aSeat(i_row + i_diffRow * i_try, i_column + i_diffColumn * i_try))
						{
							if (Is_Occupied(i_row + i_diffRow * i_try, i_column + i_diffColumn * i_try))
								i_count++;

							hasToGoNext = true;
						}
						else
							i_try++;
					}
				}
				else
					hasToGoNext = true;
			}
		}
	}

	return i_count;
}

bool SeatLayout::applyRules_Part1()
{
	std::vector<std::string> v_newSeatLayout;
	v_newSeatLayout = v_seatLayout;
	bool hasChanged = false;

	for (int i_row = 0; i_row < v_seatLayout.size(); i_row++)
	{
		for (int i_column = 0; i_column < v_seatLayout[i_row].size(); i_column++)
		{

			if (Is_aSeat(i_row, i_column))
			{
				if (Is_Occupied(i_row, i_column) && getNumberOfOccupiedAdjacentSeats(i_row, i_column) >= 4)
				{
					v_newSeatLayout[i_row][i_column] = 'L';
					hasChanged = true;
				}
				else if (!Is_Occupied(i_row, i_column) && getNumberOfOccupiedAdjacentSeats(i_row, i_column) == 0)
				{
					v_newSeatLayout[i_row][i_column] = '#';
					hasChanged = true;
				}
			}
		}
	}
	Init(v_newSeatLayout);
	return hasChanged;
}

bool SeatLayout::applyRules_Part2()
{
	std::vector<std::string> v_newSeatLayout;
	v_newSeatLayout = v_seatLayout;
	bool hasChanged = false;

	for (int i_row = 0; i_row < v_seatLayout.size(); i_row++)
	{
		for (int i_column = 0; i_column < v_seatLayout[i_row].size(); i_column++)
		{

			if (Is_aSeat(i_row, i_column))
			{
				if (Is_Occupied(i_row, i_column) && getNumberOfOccupiedApparentSeats(i_row, i_column) >= 5)
				{
					v_newSeatLayout[i_row][i_column] = 'L';
					hasChanged = true;
				}
				else if (!Is_Occupied(i_row, i_column) && getNumberOfOccupiedApparentSeats(i_row, i_column) == 0)
				{
					v_newSeatLayout[i_row][i_column] = '#';
					hasChanged = true;
				}
			}
		}
	}
	Init(v_newSeatLayout);
	return hasChanged;
}

int SeatLayout::getTheNumberOfOccupiedSeatsAtTheEnd_Part1()
{
	bool hasChanged = true;
	int i_count = 0;

	while (hasChanged)
	{
		hasChanged = applyRules_Part1();
	}

	for (int i_row = 0; i_row < v_seatLayout.size(); i_row++)
	{
		for (int i_column = 0; i_column < v_seatLayout[i_row].size(); i_column++)
		{
			if (Is_Occupied(i_row, i_column))
				i_count++;
		}
	}
	return i_count;
}

int SeatLayout::getTheNumberOfOccupiedSeatsAtTheEnd_Part2()
{
	bool hasChanged = true;
	int i_count = 0;

	while (hasChanged)
	{
		hasChanged = applyRules_Part2();
	}

	for (int i_row = 0; i_row < v_seatLayout.size(); i_row++)
	{
		for (int i_column = 0; i_column < v_seatLayout[i_row].size(); i_column++)
		{
			if (Is_Occupied(i_row, i_column))
				i_count++;
		}
	}
	return i_count;
}