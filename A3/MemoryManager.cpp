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

void MemoryManager::store(int varID, int val)
{
	//store to main if room, else store to disk
	if (!MainMemory::getInstance()->isFull())
	{
		MainMemory::getInstance()->add(varID, val);
	}
	else
	{
		Disk::getInstance()->add(varID, val);
	}
}

void MemoryManager::release(int varID)
{
	//Release from main memory and disk
	MainMemory::getInstance()->remove(varID);
	Disk::getInstance()->remove(varID);
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

void MemoryManager::swap(int varID)
{
	////TODO: We should be passing variables instead of IDs everywhere because we need to write ID and value every time
	////want to put var in main memory.
	//int varID = var.getID();
	//int val = var.getValue();

	////Check if free page in memory
	//if (!MainMemory::getInstance()->isFull())
	//{
	//	MainMemory::getInstance()->add(var);
	//}
	//else
	//{
	//	//go to main memory, find LRU
	//	//write new variable to page
	//	//get old value
	//	//write old value of page to disk
	//}

	////write to output file
	////update last access


}
