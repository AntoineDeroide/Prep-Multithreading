#include "Thread.h"
#include <iostream>

Thread::Thread(LPTHREAD_START_ROUTINE _routine, void* _params, unsigned long _ID, unsigned int _stackSize) :
	m_pRoutine(),
	m_params(_params),
	m_stackSize(_stackSize),
	m_ID(_ID),
	m_handle(),
	m_isPaused(true)
{
	SetRoutine(_routine);
	SetParams(_params);
	Init();
}

Thread::~Thread()
{
	delete m_params;

	Terminate();
}

void Thread::Init()
{
	CreateThread(
		NULL,				// Security attribs
		m_stackSize,		// Taille de la pile (si 0, par defaut 1Mb)
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

	m_isPaused = false;
	//Routine();
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
	return CloseHandle(m_handle);
}


int Thread::Pause()
{
	m_isPaused = true;
	return SuspendThread(m_handle);
}

int Thread::Resume()
{
	m_isPaused = false;
	return ResumeThread(m_handle);
}

bool Thread::IsPaused()
{
	return m_isPaused;
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

bool Thread::IsInCS()
{
	return m_isInCS;
}

void Thread::EnterCS()
{
	m_isInCS = true;
}

void Thread::LeaveCS()
{
	m_isInCS = false;
}

