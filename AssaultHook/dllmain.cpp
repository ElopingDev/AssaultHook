#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <fcntl.h>
#include "functions.h"


int ammo;

BOOL UninjectKey(int key)
{
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

// Function to patch memory values (called at DLL_PRROCESS_ATTACH)
DWORD Patch()
{
    
    MessageBoxA(NULL, "AssaultHook has been injected.", "Injection", MB_ICONINFORMATION);
    AllocConsole();
    FILE* console;
    freopen_s(&console, "CONOUT$", "w", stdout);

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, 0x0C);
    std::cout << R"(
 /\_/\
( o.o ) AssaultHook
 > ^ < 
)" 
    << std::endl;

    std::cout << "Welcome to Assault Hook!" << std::endl;
    
    // Actual Patching
    while (!UninjectKey(VK_DELETE))
    {
        

        readMem(0x00400000, 0x18AC00, 0x140, ammo);
        std::cout << ammo << std::endl;
        setMem(0x00400000, 666, 0x18AC00, 0x140); // Call the setMem function until the uninject key is pressed
        Sleep(10);
    }

    MessageBoxA(NULL, "Successfully uninjected. Please make sure to restart the game before injecting again.", "Uninjection", MB_ICONINFORMATION);
    FreeConsole();
    FreeLibraryAndExitThread((HMODULE)GetModuleHandle(0), 0);

	return 0; // Return 0 after the function has been executed (the code will keep running, not exit like i thought it would)
}

// The entry point for the DLL application
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // Check the reason for the call to DllMain
    switch (ul_reason_for_call)
    {

    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Patch, 0, 0, 0);
        break;
        // shit no one will ever use :
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// Commented like a pro :sunglasses:
// Eloping#5214