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
    void write(string, const char*);
    string read(const char*);
};

