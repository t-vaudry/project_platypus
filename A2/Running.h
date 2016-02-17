#pragma once
#include "State.h"
class Running :
	public IState
{
public:
	Running();
	~Running();
	void execute();
	void nextState();
};

