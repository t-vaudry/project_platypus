#pragma once
#include <mutex>
#include "Clock.h"
#include "Process.h"
#include "MainMemory.h"
#include "Disk.h"
#include "Variable.h"

class MemoryManager
{
private: 
	static MemoryManager* instance;
	MemoryManager();
	mutex m;
public:
	~MemoryManager();
	static MemoryManager* getInstance();
	void store(int, int);
	bool release(int);
	int lookup(int);
	void swap(int, int);
};

