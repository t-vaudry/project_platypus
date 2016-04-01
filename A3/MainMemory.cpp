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

void MainMemory::add(int varID, int value)
{
	Page tmp = Page(varID, value);
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

void MainMemory::load(int varID)
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