#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <windows.h>
#include <windowsX.h>
#include <map>
#include <set>

class Thread;

enum CriticalSectionStatus : char
{
	FREE,
	BLOCKED,

	UNDEFINED
};

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

	/*void InitCS();
	bool InsertInCS(unsigned long _ID);
	bool FreeCS();*/


	bool CheckForDeadLock();
	//void HandleDeadLock(); // Possible de sortir de la deadlock ? En terminant les threads "facultatifs" ou en en mettant en pause ?

	void Update();

private:
	std::map<unsigned long, Thread*> m_threadMap; // thread pool
	std::set<Thread*> m_activeThreads;
	std::set<Thread*> m_pausedThreads;
	
	unsigned int m_nextID;

	//struct // m_CS
	//{
	//	LPCRITICAL_SECTION self;
	//	CriticalSectionStatus status;
	//	Thread* blockingThread;
	//	unsigned long threadID;
	//} m_CS;
};

#endif // THREAD_MANAGER_H