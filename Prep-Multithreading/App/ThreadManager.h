#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <windows.h>
#include <windowsX.h>
#include <map>
#include <set>

class Thread;

class ThreadManager
{
public:
	static ThreadManager& Instance();

	ThreadManager();
	~ThreadManager();

	Thread* CreateThread(LPTHREAD_START_ROUTINE _routine, void* _params, unsigned int _stackSize = 0, unsigned long _ID = 0);
	bool DeleteThread(unsigned long _ID);

	bool PauseThread(unsigned long _ID);
	bool ResumeThread(unsigned long _ID);

	void Update();

private:
	std::map<unsigned long, Thread*> m_threadMap; // thread pool
	std::set<Thread*> m_activeThreads;
	std::set<Thread*> m_pausedThreads;
	
	unsigned int m_nextID;
};

#endif // THREAD_MANAGER_H