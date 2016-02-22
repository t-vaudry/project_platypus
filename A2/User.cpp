#include "User.h"


User::User()
{
}

User::User(string n, int numProcesses, Process* processes)
{
	name = n;
	numberOfProcesses = numProcesses;
	processList = processes;
}

User::~User()
{
}

string User::GetName()
{
	return name;
}

void User::SetName(char n)
{
	name = n;
}

int User::GetNumberOfProcesses()
{
	return numberOfProcesses;
}

void User::SetNumberOfProcesses(int n)
{
	numberOfProcesses = n;
}

bool User::IsActive()
{
	bool active = false;
	for (int i = 0; i < numberOfProcesses; i++)
	{
		if (processList[i].getState() != 1)
		{
			active = true;
			break;
		}
	}
	return active;
}

int User::ActiveProcesses()
{
	int num = 0;
	for (int i = 0; i < GetNumberOfProcesses(); i++)
		if (processList[i].IsActive())
			num++;

	return num;
}