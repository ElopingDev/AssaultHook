#pragma once
#include <Windows.h>
#include <vector>

void setMem(DWORD baseaddress, int value, DWORD addr, std::vector<DWORD> offsets);

void readMem(DWORD baseaddress, DWORD addr, DWORD offset1, int& result);
