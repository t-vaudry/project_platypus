#pragma once
#include <iostream>
#include <vector>
using namespace std;
class InstructionParser
{
public:
	InstructionParser();
	~InstructionParser();
	vector<int> parse(stringstream);
};

