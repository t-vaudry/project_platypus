#include "MemoryManager.h"


MemoryManager::MemoryManager()
{
}


MemoryManager::~MemoryManager()
{
}

MemoryManager* MemoryManager::instance;

MemoryManager* MemoryManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new MemoryManager();
	}
	return instance;
}

void MemoryManager::store(int, int)
{

}

void MemoryManager::release(int)
{

}

void MemoryManager::lookup(int)
{

}

void MemoryManager::swap(int id1)
{
	//wants to put id1 in main memory.
	//go to main memory, find LRU
	//write new vaiable to page
	//get old value
	//write old value of page to disk
	//write to output file
}
