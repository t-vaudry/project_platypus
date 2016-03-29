#include "MemoryManager.h"


MemoryManager::MemoryManager()
{
}


MemoryManager::~MemoryManager()
{
}

MemoryManager* MemoryManager::getInstance()
{
	return instance;
}

void MemoryManager::store(int, int)
{
	//check if main memory has empty slot
	//if yes, store in main
	//else, store in disk

}

void MemoryManager::release(int)
{
	//search main memory
	//if in main, delete
	//else, search disk
	//release
}

void MemoryManager::lookup(int)
{
	//get in main memory
	//if null, load LRU into main
	//get from main
}
