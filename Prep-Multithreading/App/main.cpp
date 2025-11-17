#include <windows.h>
#include "Thread.h"

int main(int* argc, char** argv)
{
    DWORD thread_id;

    // Dummy memory allocation 
    LPVOID params = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(DWORD) * 100);

    // On créé le thread
    HANDLE thread = CreateThread(
        NULL, // Security attributes 
        0, // Stack size 
        ThreadRoutine,
        params,
        0, // Le thread démarre immédiatement 
        &thread_id
    );

    if (thread == NULL) {
        //printf("Failed to create thread, thread ID : %d", thread_id);
        ExitProcess(3);
    }

    DWORD wait_res = WaitForSingleObject(thread, INFINITE);
    if (wait_res != 0) {
        //printf("Thread returned with error : %d \n", res);
    }

    // Supprimer l'objet thread 
    BOOL thread_destruction_res = CloseHandle(thread);


    Thre

    return 0;
}
