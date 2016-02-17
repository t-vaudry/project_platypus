#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include "User.h"

using namespace std;

class IOManager
{
private:
	fstream inputFile;
	fstream outputFile;
public:
	IOManager();
	~IOManager();
	void Write(char*);
	void Read(User* &);
};

