#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class IOManager
{
private:
	fstream inputFile;
	fstream outputFile;
public:
	IOManager();
	~IOManager();
	void Write(string, const char*);
	string Read(const char*);
};

