#include <iostream>
#include "Page.h"

using namespace std;

#pragma once
class MainMemory
{
private:
	MainMemory();
	static MainMemory* instance;
	Page* pages;
	int size;
	string path;
public:
	~MainMemory();
	static MainMemory* getInstance();
	void add(int, int);
	int get(int);
	void remove(int);
	void load(int);
};

