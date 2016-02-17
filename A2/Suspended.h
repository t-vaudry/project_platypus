#pragma once
#include "State.h"
class Suspended :
	public IState
{
public:
	Suspended();
	~Suspended();
	void execute();
	void nextState();
};

