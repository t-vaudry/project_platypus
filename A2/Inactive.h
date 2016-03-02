#pragma once
#include "State.h"
class Inactive :
	public State
{
public:
	Inactive();
	~Inactive();
	void execute(void *, char, int);
};

