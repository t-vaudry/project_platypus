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

MainMemory* MainMemory::getInstance()
{
	return instance;
}

void MainMemory::add(int varID, int value)
{

}

int MainMemory::get(int varID)
{

}

void MainMemory::remove(int varID)
{

}

void MainMemory::load(int varID)
{

}