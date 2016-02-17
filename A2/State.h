#include <iostream>

using namespace std;

class State
{
public:
	State();
	virtual ~State() = 0;
	virtual void execute() = 0;
	virtual void nextState() = 0;
}