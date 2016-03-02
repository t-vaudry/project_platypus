#pragma once
#include "State.h"
class Ready :
    public State
{
public:
    Ready();
    ~Ready();
    void execute(void *, char, int);
};

