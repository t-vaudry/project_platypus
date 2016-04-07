#pragma once
#include <iostream>
#include <thread>
#include "Windows.h"

using namespace std;

class Clock
{
private:
	Clock();
	static Clock* instance;
	int time;
	void * handle;
public:
	~Clock();
	static Clock* getInstance();
	int getTime();
	thread startThread();
	void run();
	void terminate();
};

