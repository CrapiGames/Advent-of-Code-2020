#include "BootCode.h"

std::string instr[NB_INST] = { "acc","jmp","nop" };

void BootCode::Init(std::string str_filepath)
{
	std::fstream file_instructions;
	char ch_buffer[256];
	std::string str_instruction;
	Instruction *instruction;

	file_instructions.open(str_filepath);
	while (!file_instructions.eof())
	{
		file_instructions.getline(ch_buffer, 256);
		str_instruction = ch_buffer;

		instruction = new Instruction();
		instruction->Init(str_instruction);
		bootCode.push_back(instruction);
	}
}


int BootCode::CorrectAndExecuteCode()
{
	int i_accumulator = 0;
	bool hasToBeDone = true;
	bool is_terminated = false;

	for (size_t i = 0; i < bootCode.size(); i++)
	{
		hasToBeDone = true;
		if (bootCode[i]->operation == JMP_INST)
			bootCode[i]->operation = NOP_INST;
		else if (bootCode[i]->operation == NOP_INST)
			bootCode[i]->operation = JMP_INST;
		else
			hasToBeDone = false;

		if (hasToBeDone)
		{
			i_accumulator = ExecuteCode_StopBeforeRerunning(&is_terminated);

			if (is_terminated)
				return i_accumulator;
			
			if (bootCode[i]->operation == JMP_INST)
				bootCode[i]->operation = NOP_INST;
			else
				bootCode[i]->operation = JMP_INST;
		}
	}

	return i_accumulator;
}


int BootCode::ExecuteCode_StopBeforeRerunning(bool *isTerminated)
{
	int i_accumulator = 0;
	size_t i_instrNumber = 0;
	std::vector<bool> hasBeenDone;
	Instruction *instruction;

	for (size_t i = 0; i < bootCode.size(); i++)
	{
		hasBeenDone.push_back(false);
	}

	while ( i_instrNumber < bootCode.size() && !hasBeenDone[i_instrNumber])
	{
		instruction = bootCode[i_instrNumber];
		hasBeenDone[i_instrNumber] = true;

		switch (instruction->operation)
		{
		case ACC_INST:
			i_accumulator += instruction->argument;
			i_instrNumber++;
			break;
		case JMP_INST:
			i_instrNumber += instruction->argument;
			break;
		case NOP_INST:
			i_instrNumber++;
			break;
		default:
			break;
		}
	}
	*isTerminated = i_instrNumber == bootCode.size();

	return i_accumulator;
}

void Instruction::Init(std::string str_lineFromFile)
{
	char ch_arg[256] = "";
	for (int inst = 0; inst < NB_INST; inst++)
	{
		if (CompareStrings(str_lineFromFile, 0, 3, instr[inst]))
			operation = inst;
	}

	for (size_t i = 4; i < str_lineFromFile.size(); i++)
	{
		ch_arg[i - 4] = str_lineFromFile[i];
	}
	argument = atoi(ch_arg);
}