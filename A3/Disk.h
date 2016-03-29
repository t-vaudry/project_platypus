#include <iostream>

using namespace std;

#pragma once
class Disk
{
private:
	Disk();
	static Disk* instance;
	string path;
public:
	~Disk();
	static Disk* getInstance();
};

