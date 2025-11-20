#include "App.h"
#include "ThreadManager.h"
#include "SafeQueue.hpp"

#include <iostream>

DWORD WINAPI ThreadRoutineExample(SafeQueue<char> _params)
{
    std::cout << "My char is " << _params[0] << ".\n";
    //std::cout << "this is an example\n";
    return 0;
}

void App::Run(int* argc, char** argv)
{
    ThreadManager* hThreadManager = &ThreadManager::Instance();
    
    SafeQueue<char> queue(10);
    queue.Push(new char('a'));
    queue.Push(new char('b'));
    queue.Push(new char('c'));
    queue.Push(new char('d'));
    queue.Push(new char('e'));
    queue.Push(new char('f'));
    queue.Push(new char('g'));
    queue.Push(new char('h'));
    queue.Push(new char('i'));
    queue.Push(new char('j'));
    
    hThreadManager->CreateThread(LPTHREAD_START_ROUTINE(ThreadRoutineExample), &queue);
    
    while (true) 
    {
        hThreadManager->Update();
    }
}