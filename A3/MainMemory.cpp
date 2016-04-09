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