#include <iostream>

class Process
{
private:
	int readyTime;
	int serviceTime;
	int remainingTime;
	State state;
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
}