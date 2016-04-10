#include "InstructionParser.h"
#include <sstream>
#include <fstream>

using namespace std;

InstructionParser::InstructionParser()
{
}


InstructionParser::~InstructionParser()
{
}

//Parses through one instruction. The return is 
//a vector of integers, with the first integer
//corresponding to the instruction code
//(1: Store, 2: Release, 3: Lookup) and the following
//integer(s) corresponding to the parameters
//of the instruction
vector<int> InstructionParser::parse(stringstream& input)
{
	//This method returns an integer corresponding to the instruction the string holds:
	//1: Store
	//2: Release
	//3: Lookup

	//The integers following the instruction code are the parameters of the given instruction
	string instruction;
	string parameter1;
	string parameter2;

	int instructCode;
	int x1;
	int x2;

	vector<int> returnVal;

	getline(input, instruction, ' ');

	if (instruction == "Store")
	{
		getline(input, parameter1, ' ');
		getline(input, parameter2);

		instructCode = 1;
		x1 = stoi(parameter1);
		x2 = stoi(parameter2);

		returnVal.push_back(instructCode);
		returnVal.push_back(x1);
		returnVal.push_back(x2);
	}

	else if (instruction == "Release")
	{
		getline(input, parameter1, ' ');

		instructCode = 2;
		x1 = stoi(parameter1);

		returnVal.push_back(instructCode);
		returnVal.push_back(x1);
	}
	
	else if (instruction == "Lookup")
	{
		getline(input, parameter1, ' ');

		instructCode = 3;
		x1 = stoi(parameter1);

		returnVal.push_back(instructCode);
		returnVal.push_back(x1);
	}

	return returnVal;	
}
