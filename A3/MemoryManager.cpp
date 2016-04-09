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
	int random = rand() % (1000-500) + 500;
	Sleep(random);
	m.unlock();
}

void MemoryManager::release(int varID)
{
	m.lock();
	//Release from main memory and disk
	MainMemory::getInstance()->remove(varID);
	Disk::getInstance()->remove(varID);
	srand(time(NULL));
	int random = rand() % (1000 - 500) + 500;
	Sleep(random);
	m.unlock();
}

int MemoryManager::lookup(int varID)
{
	m.lock();
	//Search in main memory
	//if in main memory, return value
	int val = 0;
	if (MainMemory::getInstance()->get(varID) != -1)
	{
		val = MainMemory::getInstance()->get(varID);
	}
	else
	{
		//Delete from disk
		val = Disk::getInstance()->remove(varID);
		if (val != -1)
		{
			if (MainMemory::getInstance()->isFull())
			{
				swap(varID, val);
			}
			else
			{
				MainMemory::getInstance()->add(varID, val);
			}
		}
	}
	srand(time(NULL));
	int random = rand() % (1000 - 500) + 500;
	Sleep(random);
	m.unlock();
	return val;
}

void MemoryManager::swap(int varID, int value)
{
	vector<int> diskVar;
	diskVar = MainMemory::getInstance()->swapLRU(varID, value);
	Disk::getInstance()->add(diskVar[0], diskVar[1]);
	string output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Memory Manager, SWAP: Variable " + to_string(varID) + " with Variable " + to_string(diskVar[0]);
	IOManager::getInstance()->write(output, 0);
}
