#pragma once
#include "State.h"
class Terminated :
	public State
{
private:
	int counter;
public:
	Terminated();
	~Terminated();
	void execute(int, char, int, const char*);
};

