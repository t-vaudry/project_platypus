#pragma once
#include "State.h"
class Terminated :
    public State
{
private:
    int counter;
public:
    Terminated();
    ~Terminated();
    void execute(thread::native_handle_type&, char, int);
};

