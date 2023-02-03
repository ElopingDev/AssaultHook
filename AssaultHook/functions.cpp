#include "pch.h"
#include <windows.h>
#include <iostream>
#include <fcntl.h>

// Function to change memory value at a specified address
void setMem(DWORD baseaddress, int value, DWORD offset1, DWORD offset2)
{

	DWORD* address = (DWORD*)((*(DWORD*)(baseaddress + offset1)) + offset2); // Calculating the final address by adding the baseaddress, offset1 and offset2

	*(int*)address = value; // Change the value at the final address to the specified value

}

// Function to read memory value at specified address and store it in a variable
void readMem(DWORD baseaddress, DWORD offset1, DWORD offset2, int& result)
{
	DWORD* address = (DWORD*)(((DWORD)(baseaddress + offset1)) + offset2); // Calculating the final address by adding the baseaddress, offset1 and offset2
	result = *(int*)address; // Store the value at the final address in the result variable
}