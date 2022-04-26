#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Utility.h"

class Instruction;
class BootCode;

enum E_INSTR
{
	ACC_INST = 0,
	JMP_INST,
	NOP_INST,
	NB_INST
};

class BootCode
{
public:
	std::vector<Instruction*> bootCode;

	void Init(std::string str_filepath);
	int ExecuteCode_StopBeforeRerunning(bool *isTerminated);
	int CorrectAndExecuteCode();
};

class Instruction
{
public:
	int operation;
	int argument;

	void Init(std::string str_lineFromFile);
};