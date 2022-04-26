#include "ElvesGame.h"

void ElvesGame::Init(std::vector<int> v_i_startingNumbers)
{
	memory.clear();
	i_IdOfLastElement = 0;
	for (size_t i = 0; i < v_i_startingNumbers.size()-1; i++)
	{
		memory.insert({ v_i_startingNumbers[i], i + 1 });
	}
	i_IdOfLastElement = v_i_startingNumbers.size();
	i_lastNumber = v_i_startingNumbers[v_i_startingNumbers.size() - 1];
}

int ElvesGame::GetXthNumber(size_t i_X)
{
	int i_newNumber;

	if (i_X == i_IdOfLastElement)
		return i_lastNumber;
	else
	{
		for (size_t i = i_IdOfLastElement; i < i_X; i++)
		{
			if (memory.count(i_lastNumber) == 0)
			{
				memory.insert({ i_lastNumber, i_IdOfLastElement });
				i_newNumber = 0;
			}
			else
			{
				i_newNumber = i_IdOfLastElement - memory.at(i_lastNumber);
				memory.at(i_lastNumber) = i_IdOfLastElement;
			}
			i_lastNumber = i_newNumber;
			i_IdOfLastElement++;
		}
	}

	return i_lastNumber;
}