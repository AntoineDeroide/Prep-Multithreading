#include "ThreadManager.h"
#include "Thread.h"

#include <iostream>

Thread* ThreadManager::CreateThread(unsigned long _ID, unsigned int _stackSize)
{
	Thread* pThread = new Thread(LPTHREAD_START_ROUTINE(), new void*, _ID, _stackSize);
	if (pThread->GetHandle() == NULL)
	{
		std::cout << "[ThreadManager::CreateThread() : Failed to create thread !]\n";
		return nullptr;
	}
	m_threadArray.push_back(pThread);
}