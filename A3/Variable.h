#include <iostream>
#include "Clock.h"

using namespace std;

#pragma once
class Variable
{
private:
	int ID;
	int value;
	int lastAccess;
public:
	Variable();
	Variable(int, int);
	~Variable();
	void setID(int);
	int getID();
	void setValue(int);
	int getValue();
	void setLastAccess(int);
	int getLastAccess();
};

