#include "include/functions.h"
#include <iostream>
#include <fcntl.h>

// Function to change memory value at a specified address
void setMem(DWORD baseaddress, int value, DWORD addr, std::vector<DWORD> offsets)
{
    DWORD* address = (DWORD*)(baseaddress + addr);

    for (const auto& offset : offsets)
    {
        address = (DWORD*)(*address + offset);
    }

    *(int*)address = value;
}


void readMem(DWORD baseaddress, DWORD addr, DWORD offset2, int& result)
{
	DWORD* address = (DWORD*)((*(DWORD*)(baseaddress + addr)) + offset2); 
	result = *(int*)address;
}