#pragma once
#include <string>
#include <vector>
#include "Process.h"

using namespace std;

class User
{
private:
	string name;
	int numberOfProcesses;
	vector<Process*> processList;
	vector<Process*> activeProcesses;

public:
	User();
	~User();
	User(string, int, vector<Process*>&);
	string getName();
	void setName(char);
	int getNumberOfProcesses();
	void setNumberOfProcesses(int);
	bool isActive();
	int getNumberOfActiveProcesses();
	vector<Process*>& getActiveProcesses();
	vector<Process*>& getAllProcesses();
	bool isCompleted();
};
