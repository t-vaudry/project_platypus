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
	return 0;
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

}

bool MainMemory::isFull()
{

}