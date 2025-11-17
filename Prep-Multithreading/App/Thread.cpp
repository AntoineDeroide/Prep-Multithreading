#include "Thread.h"
#include <iostream>

Thread::Thread(LPTHREAD_START_ROUTINE _routine, void* _params, unsigned long _ID, unsigned int _stackSize) : 
	m_pRoutine(),
	m_params(_params),
	m_stackSize(_stackSize),
	m_ID(_ID),
	m_handle()
{
	SetRoutine(_routine);
	SetParams(_params);
}

Thread::~Thread()
{
	delete m_params;

	Terminate();
}

void Thread::Create()
{
	CreateThread(
		NULL,				// Security attribs
		m_stackSize,		// Taille de la pile
		m_pRoutine,			// Point d'entree du thread ( ~= methode qui constitue le thread)
		m_params,			// Parametres a envoyer dans ledit point d'entree
		0,					// Delai de creation du thread (ici il demarre immediatement)
		&m_ID				// ID du thread
	);
	 
	m_handle = GetCurrentThread();
	if (m_handle == NULL)
	{
		std::cout << "[Thread::Routine : Failed to create Thread !]\n";
		ExitProcess(-1);
	}

	Routine();
}

void Thread::Routine()
{
	while (true)
	{
		if (m_isPaused)
		{
			break;
		}

		m_pRoutine(m_params);
	}
}

bool Thread::Terminate() 
{
	CloseHandle(m_handle);
}


int Thread::Pause()
{
	return SuspendThread(m_handle);
}

int Thread::Resume()
{
	return ResumeThread(m_handle);
}

HANDLE& Thread::GetHandle()
{
	return m_handle;
}

void Thread::SetRoutine(DWORD(* _routine)(void*))
{
	m_pRoutine = _routine;
}

void Thread::SetParams(void* _params)
{
	m_params = _params;
}
