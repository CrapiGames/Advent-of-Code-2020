#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "Utility.h"

enum DIRECTION
{
	EAST_DIR,
	SOUTH_DIR,
	WEST_DIR,
	NORTH_DIR
};

enum INSTRUCTION
{
	E_INSTR,
	S_INSTR,
	W_INSTR,
	N_INSTR,
	L_INSTR,
	R_INSTR,
	F_INSTR
};

class FerryBoat;
class NavigationInstructions;

class NavigationInstructions
{
public:
	std::vector<std::string> v_str_instructions;

	void Init(std::string str_filepath);
};

class FerryBoat
{
public:
	int i_position[2];
	int i_direction;
	NavigationInstructions *navigationInstructions;
	int i_waypoint[2];

	void Init(int i_dir, std::string str_filepath);
	void FollowInstruction_Part1(int i_instr, int i_quantity);
	void FollowInstruction_Part2(int i_instr, int i_quantity);
	void TurnRight90();
	void TurnRight90_waypoint();
	int GetManhattanDistance();
	int FollowInstructionsAndGetManhattanDistance_Part1();
	int FollowInstructionsAndGetManhattanDistance_Part2();
};