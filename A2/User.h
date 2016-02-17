#pragma once
#include "Process.h"
class User
{
private:
	char name;
	int numberOfProcesses;
	Process* processList;

public:
	User();
	~User();
	char GetName();
	void SetName(char);
	int GetNumberOfProcesses();
	void SetNumberOfProcesses(int);
};

