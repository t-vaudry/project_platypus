#pragma once
#include "State.h"
class Ready :
    public State
{
public:
    Ready();
    ~Ready();
    void execute(thread::native_handle_type&, char, int);
};

