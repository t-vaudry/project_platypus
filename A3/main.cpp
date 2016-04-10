#include <iostream>
#include "MemoryManager.h"
#include "ProcessManager.h"
#include "IOManager.h"
#include "MainMemory.h"
#include "Disk.h"
#include "Clock.h"

using namespace std;

int main(int argc, char* argv)
{
	//Instantiate all singletons
	IOManager::getInstance();
	MainMemory::getInstance();
	Disk::getInstance();
	MemoryManager::getInstance();
	ProcessManager::getInstance();
	Clock::getInstance();

	//Start the clock
	thread clk = Clock::getInstance()->startThread();
	//Start the process manager
	thread processManager = ProcessManager::getInstance()->startThread();

	//Join threads to main
	clk.join();
	processManager.join();

	return 0;	
}