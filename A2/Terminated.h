#pragma once
#include "State.h"
class Terminated :
	public IState
{
public:
	Terminated();
	~Terminated();
	void execute();
	void nextState();
};

