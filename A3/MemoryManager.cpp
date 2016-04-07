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
	m.lock();
	//store to main if room, else store to disk
	if (!MainMemory::getInstance()->isFull())
	{
		MainMemory::getInstance()->add(varID, val);
	}
	else
	{
		Disk::getInstance()->add(varID, val);
	}
	srand(time(NULL));
	Sleep(rand() % 1000 + 1);
	m.unlock();
}

void MemoryManager::release(int varID)
{
	m.lock();
	//Release from main memory and disk
	MainMemory::getInstance()->remove(varID);
	Disk::getInstance()->remove(varID);
	srand(time(NULL));
	Sleep(rand() % 1000 + 1);
	m.unlock();
}

int MemoryManager::lookup(int varID)
{
	m.lock();
	//Search in main memory
	//if in main memory, return value
	if (MainMemory::getInstance()->get(varID) != -1)
	{
		int val = MainMemory::getInstance()->get(varID);
		srand(time(NULL));
		Sleep(rand() % 1000 + 1);
		m.unlock();
		return val;
	}
	else
	{
		//Delete from disk
		int val = Disk::getInstance()->remove(varID);

		//Add to main memory
		swap(varID,val);
		srand(time(NULL));
		Sleep(rand() % 1000 + 1);
		m.unlock();
		return val;
	}
}

void MemoryManager::swap(int varID, int value)
{
	vector<int> diskVar;
	diskVar = MainMemory::getInstance()->swapLRU(varID, value);
	Disk::getInstance()->add(diskVar[0], diskVar[1]);
	string output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Memory Manager, SWAP: Variable " + to_string(varID) + " with Variable " + to_string(diskVar[0]);
	IOManager::getInstance()->write(output, 0);
}
