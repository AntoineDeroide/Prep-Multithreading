#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <windowsX.h>
#include <vector>

class Thread;

class ThreadManager
{
public:
	Thread* CreateThread(unsigned long _ID, unsigned int _stackSize);


private:
	std::vector<Thread*> m_threadArray;


};

#endif // THREAD_MANAGER_H