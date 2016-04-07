#include "MainMemory.h"

MainMemory::MainMemory()
{
	//path = 
	//size =
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

void MainMemory::add(Variable& var)
{
	Page tmp;
	tmp.setVariable(var);
	for (int i = 0; i < size; i++)
	{
		if (pages[i].empty())
			pages[i] = tmp;
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

void MainMemory::load(Variable&)
{
	//Won't this just be add?
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

void MainMemory::removeLRUPage()
{
	int returnPage;
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

	//Remove that page
	//pages
}