#include "App.h"
#include "ThreadManager.h"

#include <iostream>

DWORD WINAPI ThreadRoutineExample(/*int number, char* word*/ LPVOID _params)
{
    //std::cout << "My number is " << number << " and my word is " << word << ".\n";
    std::cout << "this is an example\n";
}

void App::Run(int* argc, char** argv)
{
    ThreadManager* hThreadManager = &ThreadManager::Instance();
    
    while (true) 
    {
        hThreadManager->CreateThread(ThreadRoutineExample, new void*);

        hThreadManager->Update();
    }
}