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

}

int MainMemory::get(int varID)
{
	return 0;
}

void MainMemory::remove(int varID)
{

}

void MainMemory::load(int varID)
{

}