#include <iostream>

class Process
{
private:
	int readyTime;
	int serviceTime;
public:
	Process();
	~Process();
	int GetReadyTime();
	void SetReadyTime(int);
	int GetServiceTime();
	void SetServiceTime(int);
	void Suspend();
	void Wake();
}