#include "pch.h"
#include <windows.h>
#include <iostream>

BOOL UninjectKey(int key)
{
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

// Function to change memory value at a specified address
void setMem(DWORD baseaddress, int value, DWORD offset1, DWORD offset2, bool msg)
{
    
	DWORD* address = (DWORD*)((*(DWORD*)(baseaddress + offset1)) + offset2); // Calculating the final address by adding the baseaddress, offset1 and offset2

    
	if (msg) // If the msg variable is true, display a message box with the final address
	{
		char szTest[10];
		sprintf_s(szTest, "The final address is : %X", address);
		MessageBoxA(NULL, szTest, NULL, NULL);
	}

    
	*(int*)address = value; // Change the value at the final address to the specified value
	
}

// Function to patch memory values (called at DLL_PRROCESS_ATTACH)
DWORD Patch()
{
    
	 // Call the setMem function with baseaddress, value, offset1, offset2 and msg values

    while (!UninjectKey(VK_DELETE))
    {
        setMem(0x00400000, 666, 0x18AC00, 0x140, false); // Call the setMem function until the uninject key is pressed
        Sleep(10);
    }
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