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
	static Disk* getInstance();
};

