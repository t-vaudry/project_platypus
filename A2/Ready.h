#pragma once
#include "State.h"
class Ready :
	public IState
{
public:
	Ready();
	~Ready();
	void execute();
	void nextState();
};

