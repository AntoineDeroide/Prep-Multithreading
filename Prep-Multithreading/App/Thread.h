#ifndef THREAD_H
#define THREAD_H

#include <Windows.h>
#include <WindowsX.h>

class Thread
{
public:
	Thread(
		LPTHREAD_START_ROUTINE _routine, 
		void* _params,
		unsigned long _ID, 
		unsigned int _stackSize
	);
	~Thread();

	int Pause();
	int Resume();
	bool IsPaused();

	void Routine();

	HANDLE& GetHandle();

	void SetRoutine(DWORD (*_routine)(void*)); // Le premier void est le type de retour, ensuite le deuxieme void* correspond a l'argument
	void SetParams(void* _params);

private:
	DWORD (*m_pRoutine)(void* _params); 
	void* m_params;
	unsigned int m_stackSize;
	unsigned long m_ID;
	HANDLE m_handle;

	bool m_isPaused;

	void Init();
	bool Terminate();

public:
	bool IsInCS();
	void EnterCS();
	void LeaveCS();

private:
	bool m_isInCS;
};

#endif // THREAD_H