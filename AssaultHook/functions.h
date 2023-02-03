#pragma once
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <fcntl.h>
void setMem(DWORD baseaddress, int value, DWORD offset1, DWORD offset2);
void readMem(DWORD baseaddress, DWORD offset1, DWORD offset2, int& result);