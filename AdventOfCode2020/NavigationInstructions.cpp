#include "NavigationInstructions.h"

void NavigationInstructions::Init(std::string str_filepath)
{
	std::fstream file_instructions;
	char ch_buffer[256];
	std::string str_instruction;
	std::string str_integer;
	file_instructions.open(str_filepath);
	
	while (!file_instructions.eof())
	{
		file_instructions.getline(ch_buffer, 256);
		str_instruction = ch_buffer;

		v_str_instructions.push_back(str_instruction);
	}
}



void FerryBoat::Init(int i_dir, std::string str_filepath)
{
	i_position[0] = 0;
	i_position[1] = 0;
	i_direction = i_dir;
	i_waypoint[0] = 10;
	i_waypoint[1] = 1;

	navigationInstructions = new NavigationInstructions();
	navigationInstructions->Init(str_filepath);
}

void FerryBoat::FollowInstruction_Part1(int i_instr, int i_quantity)
{
	switch (i_instr)
	{
	case E_INSTR:
		i_position[0] += i_quantity;
		break;

	case S_INSTR:
		i_position[1] -= i_quantity;
		break;

	case W_INSTR:
		i_position[0] -= i_quantity;
		break;

	case N_INSTR:
		i_position[1] += i_quantity;
		break;

	case R_INSTR:
		switch (i_quantity)
		{
		case 90:
			TurnRight90();
			break;
		case 180:
			TurnRight90();
			TurnRight90();
			break;
		case 270:
			TurnRight90();
			TurnRight90();
			TurnRight90();
			break;
		}
		break;

	case L_INSTR:
		switch (i_quantity)
		{
		case 90:
			TurnRight90();
			TurnRight90();
			TurnRight90();
			break;
		case 180:
			TurnRight90();
			TurnRight90();
			break;
		case 270:
			TurnRight90();
			break;
		}
		break;

	case F_INSTR:
		switch (i_direction)
		{
		case EAST_DIR:
			i_position[0] += i_quantity;
			break;
		case SOUTH_DIR:
			i_position[1] -= i_quantity;
			break;
		case WEST_DIR:
			i_position[0] -= i_quantity;
			break;
		case NORTH_DIR:
			i_position[1] += i_quantity;
			break;
		}
		break;
	}
}

void FerryBoat::FollowInstruction_Part2(int i_instr, int i_quantity)
{
	switch (i_instr)
	{
	case E_INSTR:
		i_waypoint[0] += i_quantity;
		break;

	case S_INSTR:
		i_waypoint[1] -= i_quantity;
		break;

	case W_INSTR:
		i_waypoint[0] -= i_quantity;
		break;

	case N_INSTR:
		i_waypoint[1] += i_quantity;
		break;

	case R_INSTR:
		switch (i_quantity)
		{
		case 90:
			TurnRight90_waypoint();
			break;
		case 180:
			TurnRight90_waypoint();
			TurnRight90_waypoint();
			break;
		case 270:
			TurnRight90_waypoint();
			TurnRight90_waypoint();
			TurnRight90_waypoint();
			break;
		}
		break;

	case L_INSTR:
		switch (i_quantity)
		{
		case 90:
			TurnRight90_waypoint();
			TurnRight90_waypoint();
			TurnRight90_waypoint();
			break;
		case 180:
			TurnRight90_waypoint();
			TurnRight90_waypoint();
			break;
		case 270:
			TurnRight90_waypoint();
			break;
		}
		break;

	case F_INSTR:
		i_position[0] += i_quantity * i_waypoint[0];
		i_position[1] += i_quantity * i_waypoint[1];
		break;
	}
}

void FerryBoat::TurnRight90()
{
	switch (i_direction)
	{
	case EAST_DIR:
		i_direction = SOUTH_DIR;
		break;
	case SOUTH_DIR:
		i_direction = WEST_DIR;
		break;
	case WEST_DIR:
		i_direction = NORTH_DIR;
		break;
	case NORTH_DIR:
		i_direction = EAST_DIR;
		break;
	}
}

void FerryBoat::TurnRight90_waypoint()
{
	int i_buffer;

	i_buffer = i_waypoint[1];
	i_waypoint[1] = -i_waypoint[0];
	i_waypoint[0] = i_buffer;
}

int FerryBoat::GetManhattanDistance()
{
	return static_cast<int>(abs(i_position[0]) + abs(i_position[1]));
}

int FerryBoat::FollowInstructionsAndGetManhattanDistance_Part1()
{
	int i_instr = 0;
	int i_quantity = 0;
	std::string str_instruction;
	std::string str_integer;

	for (size_t i = 0; i < navigationInstructions->v_str_instructions.size(); i++)
	{
		str_instruction = navigationInstructions->v_str_instructions[i];
		if (CompareStrings(str_instruction, 0, 1, "E"))
			i_instr = E_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "S"))
			i_instr = S_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "W"))
			i_instr = W_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "N"))
			i_instr = N_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "R"))
			i_instr = R_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "L"))
			i_instr = L_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "F"))
			i_instr = F_INSTR;

		str_integer = str_instruction.substr(1);
		i_quantity = stoi(str_integer);

		FollowInstruction_Part1(i_instr, i_quantity);
	}
	return GetManhattanDistance();
}

int FerryBoat::FollowInstructionsAndGetManhattanDistance_Part2()
{
	int i_instr = 0;
	int i_quantity = 0;
	std::string str_instruction;
	std::string str_integer;

	for (size_t i = 0; i < navigationInstructions->v_str_instructions.size(); i++)
	{
		str_instruction = navigationInstructions->v_str_instructions[i];
		if (CompareStrings(str_instruction, 0, 1, "E"))
			i_instr = E_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "S"))
			i_instr = S_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "W"))
			i_instr = W_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "N"))
			i_instr = N_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "R"))
			i_instr = R_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "L"))
			i_instr = L_INSTR;
		else if (CompareStrings(str_instruction, 0, 1, "F"))
			i_instr = F_INSTR;

		str_integer = str_instruction.substr(1);
		i_quantity = stoi(str_integer);

		FollowInstruction_Part2(i_instr, i_quantity);
	}
	return GetManhattanDistance();
}