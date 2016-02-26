#pragma once
#include "Process.h"
#include <string>
#include <vector>

using namespace std;

class User
{
private:
	string name;
	int numberOfProcesses;
	vector<Process*> processList;

public:
	User();
	~User();
	User(string, int, vector<Process*>&);
	string GetName();
	void SetName(char);
	int GetNumberOfProcesses();
	void SetNumberOfProcesses(int);
	bool IsActive();
	int ActiveProcesses();
	vector<Process*>& GetActiveProcesses();
	vector<Process*>& GetAllProcesses();
	bool Completed();
};
