#include "User.h"

User::User()
{
}

User::User(string n, int numProcesses, vector<Process*>& processes)
{
	name = n;
	numberOfProcesses = numProcesses;
	processList = processes;
}

User::~User()
{
}

string User::getName()
{
	return name;
}

void User::setName(char n)
{
	name = n;
}

int User::getNumberOfProcesses()
{
	return numberOfProcesses;
}

void User::setNumberOfProcesses(int n)
{
	numberOfProcesses = n;
}

/*************************************************
The isActive function returns a boolean value to 
indicate if a user has at least one active process
*************************************************/
bool User::isActive()
{
	bool active = false;
	for (int i = 0; i < numberOfProcesses; i++)
	{
		//States 1 and 4 are Terminated and Inactive, respectively
		if (processList[i]->getState() != 1 && processList[i]->getState() != 4)
		{
			active = true;
			break;
		}
	}
	return active;
}

int User::getNumberOfActiveProcesses()
{
	int temp = 0;
	for (int i = 0; i < getNumberOfProcesses(); i++)
		if (processList[i]->isActive())
		{
			temp++;
		}

	return temp;
}

vector<Process*>& User::getActiveProcesses()
{
	//Clear list upon entering function for each new time quantum
	activeProcesses.clear();

	//Fill activeProcesses with the processes of that time quantum
	for (int i = 0; i < getNumberOfProcesses(); i++)
		if (processList[i]->isActive())
		{
			activeProcesses.push_back(processList[i]);
		}

	return activeProcesses;
}

vector<Process*>& User::getAllProcesses()
{
	return processList;
}

/*************************************************
The isCompleted function returns a boolean value to
indicate if a user has all terminated processes
*************************************************/
bool User::isCompleted()
{
	for (int i = 0; i < getNumberOfProcesses(); i++)
		if (processList[i]->getState() != 1)
		{
			return false;
		}
	return true;
}