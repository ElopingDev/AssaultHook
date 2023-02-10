#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <fcntl.h>
#include "include/functions.h"
#include "include/hacks.h"

DWORD WINAPI HackThread(LPVOID instance)
{
    const auto baseaddress = reinterpret_cast<std::uintptr_t>(GetModuleHandle("ac_client.exe"));
    
    std::cout << R"(
 /\_/\
( o.o ) AssaultHook
 > ^ < 
)" << std::endl;
    std::cout << "Welcome to Assault Hook!" << std::endl;
    
    while (!GetAsyncKeyState(VK_END))
    { 
        AmmoHack(baseaddress);
        Sleep(10);
    }

    MessageBoxA(NULL, "Successfully uninjected.", "AssaultHook", NULL);
    FreeConsole();
    FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);

}

BOOL APIENTRY DllMain(HINSTANCE instance, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    {
        if (ul_reason_for_call == 1)
        {
            AllocConsole();
            FILE* console_in;
            FILE* console_out;
            freopen_s(&console_out, "CONOUT$", "w", stdout);
            freopen_s(&console_in, "CONIN$", "r", stdin);
            HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hStdout, 0x0C);
            DisableThreadLibraryCalls(instance);

            const HANDLE thread = CreateThread(
                nullptr,
                NULL,
                HackThread,
                instance,
                NULL,
                nullptr
            );
            if (thread)
                MessageBoxA(NULL, "RatioHook Injected", "Injection", NULL);
                CloseHandle(thread);
        }
        return TRUE;
    }

}