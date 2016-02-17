#include "IOManager.h"



IOManager::IOManager()
{
}

IOManager::~IOManager()
{
}

void IOManager::Write(char* c)
{
	if (!outputFile)
	{
		//outputFile.open('a');
	}

	outputFile << c << endl;

}

void IOManager::Read(User* &users)
{
	//Get number of users
	//Foreach user:
	//-Get number of processes
	//-Foreach process
	//Get readyTime
	//Get serviceTime
	//Set for each user
}