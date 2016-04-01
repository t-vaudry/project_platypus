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
	Page(Variable);
	~Page();
	void setVariable(Variable);
	Variable getVariable();
	int getValue();
};

