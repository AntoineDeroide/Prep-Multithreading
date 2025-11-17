#include "ThreadManager.h"
#include "Thread.h"

#include <iostream>

ThreadManager::ThreadManager() : m_threadMap(), m_nextID(0), m_activeThreads(), m_pausedThreads(), m_blockingThread(nullptr)
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
	Thread* pThread = m_threadMap.find(_ID)->second;
	delete pThread;
}

bool ThreadManager::CheckForDeadLock()
{
	int count = 0;
	for (auto i = m_threadMap.begin(); i != m_threadMap.end(); i++)
	{
		if (i->second->IsInCS())
		{
			count++;
		}

		if (count > 1)
		{
			std::cout << "[ThreadManager::CheckForDeadLock() : Multiple threads entered the programs Critical Section]\n";
			std::cout << "[ThreadManager::CheckForDeadLock() : Shutdown required]\n";
			return true;
		}
	}
	return false;
}

bool ThreadManager::PauseThread(unsigned long _ID)
{
	Thread* toHandle = m_threadMap.find(_ID)->second;

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

	return true;
}

bool ThreadManager::ResumeThread(unsigned long _ID)
{
	Thread* toHandle = m_threadMap.find(_ID)->second;

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

	return true;
}


void ThreadManager::Update()
{
	if (CheckForDeadLock())
		return;

	for (auto i = m_threadMap.begin(); i != m_threadMap.end(); i++)
	{
		if (i->second->IsInCS())
			m_blockingThread = i->second;
		
		/*if (i->second->IsPaused())
		{
			if (m_activeThreads.find(i->second) != m_activeThreads.end())
			{
				m_pausedThreads.insert(i->second);
				m_activeThreads.erase(i->second);
			}
		}*/

		// code...
	}
}
