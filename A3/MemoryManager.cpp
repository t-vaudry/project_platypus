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

//Stores a variable to memory. If the main memory has
//a free page, store in main memory. Otherwise, store
//on disk. The process sleeps for a random amount of
//time to simulate execution time.
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

//Releases a variable from memory. The variable is
//attempted to be removed from both main and disk 
//memory. The process sleeps for a random amount of
//time to simulate execution time.
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

//Looks up a variable in memory. If the variable is
//in main memory, return its value. Else, swap out the
//LRU page from main memory and store it to disk and
//place the variable with the wanted varID into
//main memory.The process sleeps for a random amount of
//time to simulate execution time.
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

//Swaps a value from the main memory to the disk.
void MemoryManager::swap(int varID, int value)
{
	vector<int> diskVar;
	diskVar = MainMemory::getInstance()->swapLRU(varID, value);
	Disk::getInstance()->add(diskVar[0], diskVar[1]);
	string output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Memory Manager, SWAP: Variable " + to_string(varID) + " with Variable " + to_string(diskVar[0]);
	IOManager::getInstance()->write(output, 0);
}
