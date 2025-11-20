#include "ThreadManager.h"
#include "Thread.h"

#include <iostream>

ThreadManager::ThreadManager() : m_threadMap(), m_nextID(0), m_activeThreads(), m_pausedThreads()
{
	// code...
}

ThreadManager::~ThreadManager()
{
	for (auto i = m_threadMap.begin(); i != m_threadMap.end(); i++)
	{
		delete i->second;
	}
}

ThreadManager& ThreadManager::Instance()
{
	static ThreadManager instance = ThreadManager();
	return instance;
}

Thread* ThreadManager::CreateThread(LPTHREAD_START_ROUTINE _routine, void* _params, unsigned int _stackSize, unsigned long _ID)
{
	Thread* pThread = new Thread(_routine, _params, _ID, _stackSize);
	if (pThread->GetHandle() == NULL)
	{
		std::cout << "[ThreadManager::CreateThread() : Failed to create thread !]\n";
		return nullptr;
	}
	m_nextID++;
	m_threadMap.insert(std::pair<unsigned long, Thread*>(_ID, pThread));
}

bool ThreadManager::DeleteThread(unsigned long _ID)
{
	if (m_threadMap.find(_ID) == m_threadMap.end())
		return false;

	Thread* pThread = m_threadMap.find(_ID)->second;
	if (pThread != nullptr)
		delete &pThread;
	return true;
}

bool ThreadManager::PauseThread(unsigned long _ID)
{
	Thread* toHandle = m_threadMap[_ID];

	if (toHandle == nullptr)
	{
		std::cout << "ThreadManager::PauseThread() : Failed to pause thread " << _ID << ", this thread doesn't exist !\n";
		return false;
	}

	if (toHandle->IsPaused())
	{
		std::cout << "ThreadManager::PauseThread() : Failed to pause thread " << _ID << ", this thread is already suspended !\n";
		return false;
	}
	
	if (toHandle->Pause() == -1)
	{
		std::cout << "ThreadManager::PauseThread() : Failed to pause thread " << _ID << std::endl;
		return false;
	}

	m_pausedThreads.insert(toHandle);

	return true;
}

bool ThreadManager::ResumeThread(unsigned long _ID)
{
	Thread* toHandle = m_threadMap[_ID];

	if (toHandle == nullptr)
	{
		std::cout << "ThreadManager::ResumeThread() : Failed to resume thread " << _ID << ", this thread doesn't exist !\n";
		return false;
	}

	if (toHandle->IsPaused() == false)
	{
		std::cout << "ThreadManager::ResumeThread() : Failed to resume thread " << _ID << ", this thread is already active !\n";
		return false;
	}
	
	if (toHandle->Resume() == -1)
	{
		std::cout << "ThreadManager::ResumeThread() : Failed to resume thread " << _ID << std::endl;
		return false;
	}
	m_activeThreads.insert(toHandle);

	return true;
}

void ThreadManager::Update()
{
	for (auto i = m_threadMap.begin(); i != m_threadMap.end(); i++)
	{
		i->second->Routine();

		// code...
	}
}
