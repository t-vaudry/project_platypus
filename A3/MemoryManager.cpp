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
	//store to main if room, else store to disk?
	if (!MainMemory::getInstance()->isFull())
	{
		//MainMemory::getInstance()->add()
	}
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
		int val = Disk::getInstance()->remove(varID);

		//Add to main memory
		swap(varID,val);
		return val;
	}
}

void MemoryManager::swap(int varID, int value)
{
	vector<int> diskVar;
	diskVar = MainMemory::getInstance()->swapLRU(varID, value);
	Disk::getInstance()->add(diskVar[0], diskVar[1]);
}
