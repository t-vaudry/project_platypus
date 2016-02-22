#pragma once
#include "State.h"
class Suspended :
	public State
{
private:
	int counter;
public:
	Suspended();
	~Suspended();
	void execute(int, char, int, const char*);
};


