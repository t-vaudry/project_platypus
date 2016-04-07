#pragma once
#include "Clock.h"
#include "InstructionParser.h"
#include "Process.h"
#include "MainMemory.h"
#include "Disk.h"
#include "Variable.h"

class MemoryManager
{
private: 
	static MemoryManager* instance;
	//InstructionParser parser;
	Process* processes;
	MemoryManager();

public:
	~MemoryManager();
	static MemoryManager* getInstance();
	void store(int, int);
	void release(int);
	int lookup(int);
	void swap(int, int);
};

