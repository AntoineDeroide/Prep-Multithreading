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

	void SetRoutine(DWORD (*_routine)(void*)); // Le premier void est le type de retour, ensuite le deuxieme void* correspond a l'argument
	void SetParams(void* _params);

	HANDLE& GetHandle();

	// A deplacer dans ThreadManager ?
	//////////////////
	int Pause();	//
	int Resume();	//
	//////////////////

private:
	DWORD (*m_pRoutine)(void* _params); // declaration d'un pointeur de fonction
	void* m_params;
	unsigned int m_stackSize;
	unsigned long m_ID;
	HANDLE m_handle;

	bool m_isPaused;

	void Create();
	void Routine(); // ( / comportement du thread)

public:
	//void EnterCS();
	//void LeaveCS();

private:
	//bool m_isInCS;

	bool Terminate();


};

#endif // THREAD_H