#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "Clock.h"

using namespace std;

class IOManager
{
private:
	IOManager();
	static IOManager* instance;
	const char* processPath;
	const char* memconfigPath;
	const char* outputPath;
	const char* diskPath;
	const char* tmpPath;
public:
	~IOManager();
	static IOManager* getInstance();
	void write(string, int);
	string read(int);
	void removeLine(int);
};

