#pragma once
#include "State.h"
class Running :
    public State
{
private:
    int counter;
public:
    Running();
    ~Running();
    void execute(int, char, int, const char*);
};

