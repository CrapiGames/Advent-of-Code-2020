#include <fstream>
#include <string>
#include <iostream>

#include "ExpenseReport.h"
#include "PasswordListAndPolicy.h"
#include "TreeMap.h"
#include "PassportBatch.h"
#include "BoardingPasses.h"
#include "DeclarationFormAnswers.h"
#include "ColorBagRules.h"
#include "BootCode.h"
#include "XMASNumbers.h"
#include "Adapters.h"
#include "SeatLayout.h"
#include "NavigationInstructions.h"
#include "BusServices.h"
#include "BitmaskSystem.h"
#include "ElvesGame.h"
#include "TicketTrain.h"
#include "ConwayCubes.h"
#include "NewMath.h"
#include "MonsterMessage.h"
#include "JurrassicJigsaw.h"

// IMPORTANT DATA TO CHECK
int i_dayOfTheAdvent = 17;
bool is_Testing = false;


std::string getInputFilePath(int i_dayAdvent, bool is_testing);

int main(int argc, char *argv[])
{
	std::string str_inputFilePath = getInputFilePath(i_dayOfTheAdvent, is_Testing);
	std::vector<int> v_i_startingNumbers;


	switch (i_dayOfTheAdvent)
	{
	case 19:
		MonsterMessages *monsterMessages;
		monsterMessages = new MonsterMessages();
		monsterMessages->Init(str_inputFilePath);

		std::cout << "The number of messages completely matching rule 0 is : " << monsterMessages->GetNumberOfMessagesMatchingRule0() << std::endl;

		monsterMessages->m_str_rules["8"] = "42 | 42 8";
		monsterMessages->m_str_rules["11"] = "42 31 | 42 11 31";

		std::cout << "The number of messages completely matching rule 0 is : " << monsterMessages->GetNumberOfMessagesMatchingRule0_Loop() << std::endl;

		break;

	case 18:
		NewMath *newMath;
		newMath = new NewMath();
		newMath->Init(str_inputFilePath);

		std::cout << "The sum of each result is (Part1) : " << newMath->GetSumOfSolutions_Part1() << std::endl;
		std::cout << "The sum of each result is (Part2) : " << newMath->GetSumOfSolutions_Part2() << std::endl;

		break;

	case 17:
		ConwayCubes3D *conwayCubes3D;
		conwayCubes3D = new ConwayCubes3D();
		conwayCubes3D->Init(str_inputFilePath);

		std::cout << "The number of active cubes 3-D after the sixth cycle is : " << conwayCubes3D->GetSumOfActiveAfterCycles(6) << std::endl; // 255

		ConwayCubes4D *conwayCubes4D;
		conwayCubes4D = new ConwayCubes4D();
		conwayCubes4D->Init(str_inputFilePath);

		std::cout << "The number of active cubes 4-D after the sixth cycle is : " << conwayCubes4D->GetSumOfActiveAfterCycles(6) << std::endl; // 2340
		break;

	case 16:
		TrainTickets *trainTickets;
		trainTickets = new TrainTickets();
		trainTickets->Init(str_inputFilePath);

		std::cout << "The ticket scanning error rate is : " << trainTickets->GetSumOfAllInvalid() << std::endl; //21071
		std::cout << "The produce of departure values is : " << trainTickets->GetTheProduceOfDepartureFields() << std::endl; // 3429967441937
		break;

	case 15:
		ElvesGame *elvesGame;
		elvesGame = new ElvesGame();
		v_i_startingNumbers = { 0,13,16,17,1,10,6 };
		elvesGame->Init(v_i_startingNumbers);

		std::cout << "The 2020th Number is : " << elvesGame->GetXthNumber(2020) << std::endl; //276
		std::cout << "The 2020th Number is : " << elvesGame->GetXthNumber(30000000) << std::endl; //31916
		break;

	case 14:
		BitmaskSystem *bitmaskSystem;
		bitmaskSystem = new BitmaskSystem();
		bitmaskSystem->Init(str_inputFilePath);

		std::cout << "The sum of memory datas is (Part1) : " << bitmaskSystem->GetSumOfMemoryDataAfterProcessing_Part1() << std::endl; // 11501064782628

		bitmaskSystem->Init(str_inputFilePath);
		std::cout << "The sum of memory datas is (Part2) : " << bitmaskSystem->GetSumOfMemoryDataAfterProcessing_Part2() << std::endl; // 5142195937660
		break;

	case 13:
		BusSevices *busServices;
		busServices = new BusSevices();
		busServices->Init(str_inputFilePath);

		std::cout << "The Id of the earliest bus multiplied by the number of minutes to wait is : " << busServices->GetTheEarliestBusIdByWaitingMinutes() << std::endl; // 102
		std::cout << "The earliest timestamp corresponding the offsets is : " << busServices->GetTheEarliestSubsequentDeparture() << std::endl; // 327300950120029
		break;

	case 12:
		FerryBoat *ferryBoat;
		ferryBoat = new FerryBoat();
		ferryBoat->Init(EAST_DIR, str_inputFilePath);

		std::cout << "The Manhattan Distance after following isntructions (Part 1) is : " << ferryBoat->FollowInstructionsAndGetManhattanDistance_Part1() << std::endl; // 882

		ferryBoat->Init(EAST_DIR, str_inputFilePath);
		std::cout << "The Manhattan Distance after following isntructions (Part 2) is : " << ferryBoat->FollowInstructionsAndGetManhattanDistance_Part2() << std::endl; // 28885
		break;

	case 11:
		SeatLayout *seatLayout;
		seatLayout = new SeatLayout();
		seatLayout->Init(str_inputFilePath);

		std::cout << "The number of end up occupied seats (Part1) is : " << seatLayout->getTheNumberOfOccupiedSeatsAtTheEnd_Part1() << std::endl; // 2166
		
		seatLayout->Init(str_inputFilePath);
		std::cout << "The number of end up occupied seats (Part2) is : " << seatLayout->getTheNumberOfOccupiedSeatsAtTheEnd_Part2() << std::endl; // 1955

		break;

	case 10:
		Adapters *adapters;
		adapters = new Adapters();
		adapters->Init(str_inputFilePath);

		std::cout << "The number of 1-jolt diff multiplied by 3-jolt diff is : " << adapters->GetThexJoltDiffNumber(1) * adapters->GetThexJoltDiffNumber(3) << std::endl; // 2170
		std::cout << "The number of possible arrangement is : " << adapters->GetTheNumberOfCombinationsFrom(0) << std::endl; // 24803586664192
		break;

	case 9:
		XMASNumbers *xmasNumbers;
		xmasNumbers = new XMASNumbers();
		int i_preambleSize;
		if (is_Testing)
			i_preambleSize = 5;
		else
			i_preambleSize = 25;

		xmasNumbers->Init(str_inputFilePath, i_preambleSize);

		std::cout << "The first number not respecting the property is : " << xmasNumbers->FindTheFirst() << std::endl; // 466456641
		std::cout << "The encryption weakness is : " << xmasNumbers->FintTheEncryptionWeakness(xmasNumbers->FindTheFirst()) << std::endl; // 55732936
		break;

	case 8:
		BootCode *bootCode;
		bool isTerminated;
		bootCode = new BootCode();
		bootCode->Init(str_inputFilePath);

		std::cout << "The accumulator value when stopped before running a second time is : " << bootCode->ExecuteCode_StopBeforeRerunning(&isTerminated) << std::endl; //1654
		std::cout << "The accumulator value whencorrected is : " << bootCode->CorrectAndExecuteCode() << std::endl; //833
		break;

	case 7:
		ColorBagRules *colorBagRules;
		colorBagRules = new ColorBagRules();
		colorBagRules->Init(str_inputFilePath);

		std::cout << "The number of bag colors that can contain shiny gold bag is : " << colorBagRules->GetNumberColorBagsThatCouldContain("shiny gold") << std::endl; //268
		std::cout << "The number of bag colors contained in a shiny gold bag is : " << colorBagRules->GetNumberOfBagsContained("shiny gold") << std::endl; //7867
		break;

	case 6:
		DeclarationFormAnswers *declarationFormAnswers;

		declarationFormAnswers = new DeclarationFormAnswers();
		declarationFormAnswers->Init(str_inputFilePath);

		std::cout << "The sum of the counts answered by anyone in group is : " << declarationFormAnswers->GetTheSumOfCounts_Anyone() << std::endl; //6530
		std::cout << "The sum of the counts answered by everyone in group is : " << declarationFormAnswers->GetTheSumOfCounts_Everyone() << std::endl; //3323
		break;

	case 5:
		BoardingPasses *boardingPasses;

		boardingPasses = new BoardingPasses();
		boardingPasses->Init(str_inputFilePath);

		std::cout << "The max seat ID found is : " << boardingPasses->GetHighestID() << std::endl; //938
		std::cout << "The seat ID found is : " << boardingPasses->GetTheSeatID() << std::endl; //696
		break;

	case 4:
		PassportBatch *passportBatch;

		passportBatch = new PassportBatch();
		passportBatch->Init(str_inputFilePath);

		std::cout << "The number of valid passports is (Part 1): " << passportBatch->CountAllValidPassportsWithoutICD_Part1() << std::endl; //196
		std::cout << "The number of valid passports is (Part 2): " << passportBatch->CountAllValidPassportsWithoutICD_Part2() << std::endl; //114

		break;
		
	case 3:
		TreeMap *treeMap;
		unsigned long multiplication;

		treeMap = new TreeMap();
		treeMap->Init(str_inputFilePath);

		multiplication = treeMap->CountTreesWithSlope(1, 1) * treeMap->CountTreesWithSlope(1, 3) * treeMap->CountTreesWithSlope(1, 5) * treeMap->CountTreesWithSlope(1, 7) * treeMap->CountTreesWithSlope(2, 1);

		std::cout << "The number of trees met is : " << treeMap->CountTreesWithSlope(1, 3) << std::endl; //156
		std::cout << "The number of trees met multiplied is : " <<  multiplication << std::endl; //3521829480

		break;

	case 2:
		PasswordList *passwordList;

		passwordList = new PasswordList();
		passwordList->Init(str_inputFilePath);

		std::cout << "The number of valid passwords is (Part 1) : " << passwordList->GetNumberOfValidPasswords_Part1() << std::endl; //528
		std::cout << "The number of valid passwords is (Part 2) : " << passwordList->GetNumberOfValidPasswords_Part2() << std::endl; //497

		break;

	case 1:
		ExpenseReport *expenseReport;

		expenseReport = new ExpenseReport();
		expenseReport->Init(str_inputFilePath);

		std::cout << "The integrity number part 1 is : " << expenseReport->CheckIntegrityReport_1() << std::endl; //538464
		std::cout << "The integrity number part 2 is : " << expenseReport->CheckIntegrityReport_2() << std::endl; //278783190
		break;

	default:
		std::cout << "No Day Found" << std::endl;
		break;

	}
}






























std::string getInputFilePath(int i_dayAdvent, bool is_testing)
{
	std::string str_inputFilePath;
	char ch_buffer[10];

	if (is_testing)
		str_inputFilePath = "Inputs/TEST.txt";
	else
	{
		str_inputFilePath = "Inputs/input";
		_itoa_s(i_dayAdvent, ch_buffer, 10);
		str_inputFilePath += ch_buffer;
		str_inputFilePath += "_1.txt";
	}

	return str_inputFilePath;
}
