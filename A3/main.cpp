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
	IOManager::getInstance();
	MainMemory::getInstance();
	Disk::getInstance();
	MemoryManager::getInstance();
	ProcessManager::getInstance();
	Clock::getInstance();

	thread clk = Clock::getInstance()->startThread();
	thread processManager = ProcessManager::getInstance()->startThread();
	clk.join();
	processManager.join();

	return 0;	
}