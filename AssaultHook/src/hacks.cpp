#include "include/hacks.h"
#include "include/functions.h"
#include <vector>

void AmmoHack(uintptr_t baseaddress) {
	std::vector<DWORD> offsets = { 0x368, 0x14, 0x0 };
	setMem(baseaddress, 666, 0x17E0A8, offsets);
}