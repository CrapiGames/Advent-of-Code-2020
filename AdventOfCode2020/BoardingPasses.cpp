#include "BoardingPasses.h"

void BoardingPasses::Init(std::string str_filepath)
{
	std::fstream file_boardingPasses;
	char ch_buffer[256];
	std::string str_BoardingPassInfo;
	file_boardingPasses.open(str_filepath);

	while (!file_boardingPasses.eof())
	{
		BoardingPass* boardingPass = new BoardingPass();

		file_boardingPasses.getline(ch_buffer, 256);
		str_BoardingPassInfo = ch_buffer;
		boardingPass->Init(str_BoardingPassInfo);

		v_boardingPasses.push_back(boardingPass);
	}

}

int BoardingPasses::GetHighestID()
{
	int i_maxIDFound = 0;
	for (auto& boardPass : v_boardingPasses)
	{
		i_maxIDFound = std::max(boardPass->GetSeatID(), i_maxIDFound);
	}
	return i_maxIDFound;
}

bool BoardingPasses::IsExisting(int i_seatId)
{
	for (auto& boardPass : v_boardingPasses)
	{
		if (boardPass->GetSeatID() == i_seatId)
			return true;
	}
	return false;
}

int BoardingPasses::GetTheSeatID()
{
	int i_seatID;
	for (int row = 1; row < 127; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			i_seatID = 8 * row + column;
			if (!BoardingPasses::IsExisting(i_seatID))
			{
				if (BoardingPasses::IsExisting(i_seatID - 1) && BoardingPasses::IsExisting(i_seatID + 1))
					return i_seatID;
			}
		}
	}
	return -1;
}


void BoardingPass::Init(std::string str_seatPart)
{
	i_row = 0;
	i_column = 0;

	if (str_seatPart.size() == 10)
	{
		str_seatPartition = str_seatPart;
		for (int i = 0; i < 7; i++)
		{
			if (CompareStrings(str_seatPartition, i, 1, "B"))
				i_row += static_cast<int>(pow(2, 6 - i));
		}
		for (int i = 7; i < 10; i++)
		{
			if (CompareStrings(str_seatPartition, i, 1, "R"))
			{
				i_column += static_cast<int>(pow(2, 2 - (i - 7)));
			}
		}

	}
	else
	{
		str_seatPartition = "";
	}
}

int BoardingPass::GetSeatID()
{
	return 8 * i_row + i_column;
}