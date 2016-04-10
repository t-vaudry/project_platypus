#include "MainMemory.h"

MainMemory::MainMemory()
{
	size = stoi(IOManager::getInstance()->read(2));
	pages = new Page[size];
}

MainMemory::~MainMemory()
{
}

MainMemory* MainMemory::instance;

MainMemory* MainMemory::getInstance()
{
	if (instance == NULL)
	{
		instance = new MainMemory();
	}
	return instance;
}

//Adds a variable to the next free page in memory.
//If there is no free page, does nothing.
void MainMemory::add(int varID, int val)
{
	Page tmp(varID, val);

	for (int i = 0; i < size; i++)
	{
		if (pages[i].empty())
		{
			pages[i] = tmp;
			break;
		}
	}
}

//Returns the value associated to a particular
//variable ID stored in main memory.
//If the variable ID is not found, return -1
int MainMemory::get(int varID)
{
	//Search for varID
	for (int i = 0; i < size; i++)
	{
		//if varID is in memory, return value
		if (pages[i].getVariable().getID() == varID)
		{
			pages[i].getVariable().setLastAccess();
			return pages[i].getValue();
		}
	}

	//else, return -1 (memoryManager will handle loading from disk to main)
	return -1;
}

//Removes a variable from main memory based
//on its variable ID. If the variable ID is
//not found, do nothing
void MainMemory::remove(int varID)
{
	for (int i = 0; i < size; i++)
	{
		if (pages[i].getVariable().getID() == varID)
		{
			pages[i] =  Page();
		}
	}
}

//Returns true if every page in memory is used.
bool MainMemory::isFull()
{
	for (int i = 0; i < size; i++)
	{
		if (pages[i].empty())
		{
			return false;
		}
	}
	return true;
}

//Searches for the page in memory least recently accessed.
//This page is replaced by a new page holding the newVarID
//and newValue. The contents of the removed page are returned
//in a vector of integers, the first containing the varID, 
//the second holding the value.
vector<int> MainMemory::swapLRU(int newVarID, int newValue)
{
	int returnPage = 0;
	int lowestAccessTime = pages[0].getVariable().getLastAccess();

	//Scan through all pages
	for (int i = 1; i < size; i++)
	{
		//Find variable with lowest lastAccess
		if (pages[i].getVariable().getLastAccess() < lowestAccessTime)
		{
			returnPage = i;
			lowestAccessTime = pages[i].getVariable().getLastAccess();
		}
	}

	vector<int> var;
	var.push_back(pages[returnPage].getVariable().getID());
	var.push_back(pages[returnPage].getValue());

	pages[returnPage] = Page(newVarID, newValue);
	return var;	
}