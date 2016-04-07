#include <iostream>
#include <vector>
#include "Clock.h"
#include "IOManager.h"
#include "Page.h"

using namespace std;

#pragma once
class MainMemory
{
private:
	static MainMemory* instance;
	Page* pages;
	int size;
	const char* path;
	MainMemory();

public:
	~MainMemory();
	static MainMemory* getInstance();
	void add(int, int);
	int get(int);
	void remove(int);
	void load(int, int);
	bool isFull();
	vector<int> swapLRU(int, int);
};

