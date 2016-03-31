#include <iostream>
#include "Clock.h"
#include "Page.h"

using namespace std;

#pragma once
class MainMemory
{
private:
	static MainMemory* instance;
	Page* pages;
	int size;
	string path;
	MainMemory();

public:
	~MainMemory();
	static MainMemory* getInstance();
	void add(int, int);
	int get(int);
	void remove(int);
	void load(int);
};
