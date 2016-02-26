#pragma once
#include "State.h"
class Ready :
    public State
{
public:
    Ready();
    ~Ready();
    void execute(int&, char, int, const char*);
};

