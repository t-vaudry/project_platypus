#include "User.h"


User::User()
{
	processList = nullptr;
}

User::~User()
{
}

char User::GetName()
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