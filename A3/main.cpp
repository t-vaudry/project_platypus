#include <iostream>
#include "MemoryManager.h"
#include "Clock.h"

using namespace std;

int main(int argc, char* argv)
{
	//Test Clock
	Clock* clk = Clock::getInstance();
	thread t = clk->startThread();
	t.join();
	return 0;
}