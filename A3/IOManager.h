#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <mutex>
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
	const char* commandPath;
	const char* tmpPath;
	mutex m;
public:
	~IOManager();
	static IOManager* getInstance();
	void write(string, int);
	string read(int);
	string readLineNumber(int);
	void removeLine(int);
	int getNumberOfLines();
};

