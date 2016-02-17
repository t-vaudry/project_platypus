#include <iostream>
#include "State.h"

class Process
{
private:
	int readyTime;
	int serviceTime;
	int remainingTime;
	IState *state;
public:
	Process();
	~Process();
	int getReadyTime();
	void setReadyTime(int);
	int getServiceTime();
	void setServiceTime(int);
	int getRemainingTime();
	void setRemainingTime(int);
	void Suspend();
	void Wake();
};