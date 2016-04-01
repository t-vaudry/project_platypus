#include <iostream>
#include "Clock.h"
#include "Variable.h"

using namespace std;

#pragma once
class Page
{
private:
	Variable var;
public:
	Page();
	Page(int, int);
	~Page();
	void setVariable(Variable);
	Variable getVariable();
	bool empty();
	int getValue();
};

