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

int MemoryManager::lookup(int varID)
{
	//Search in main memory
	//if in main memory, return value
	if (MainMemory::getInstance()->get(varID) != -1)
	{
		return MainMemory::getInstance()->get(varID);
	}
	else
	{
		//Delete from disk
		Disk::getInstance()->remove(varID);

		//Add to main memory
		swap(varID);
	}
}

void MemoryManager::swap(int id1)
{
	//TODO: We should be passing variables instead of IDs everywhere because we need to write ID and value every time
	//wants to put id1 in main memory.
	//go to main memory, find LRU
	//write new vaiable to page
	//get old value
	//write old value of page to disk
	//write to output file
	//update last access

	////Check if free page in memory
	//if (!MainMemory::getInstance()->isFull())
	//{
	//	//TODO: We do not have the value we want to write... Put 0 as place holder for now
	//	MainMemory::getInstance()->add(varID, 0);
	//}
	//else
	//{

	//}
}
