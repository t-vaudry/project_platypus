#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "Clock.h"

using namespace std;

class IOManager
{
private:
	const char* processPath;
	const char* memconfigPath;
	const char* outputPath;
	const char* diskPath;
public:
	IOManager();
	~IOManager();
	void Write(string, int);
	string Read(int);
};

