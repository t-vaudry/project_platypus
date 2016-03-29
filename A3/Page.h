#include <iostream>
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
	int getValue();
	//Variable swap(Variable);
};

