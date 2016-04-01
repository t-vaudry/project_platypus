#include <iostream>
#include "Clock.h"

using namespace std;

#pragma once
class Disk
{
private:
	Disk();
	static Disk* instance;
public:
	~Disk();
	const char* path;
	static Disk* getInstance();
};

