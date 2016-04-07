#pragma once
#include <iostream>
#include <vector>
#include "Clock.h"

using namespace std;
class InstructionParser
{
public:
	InstructionParser();
	~InstructionParser();
	vector<int> parse(stringstream&);
};

