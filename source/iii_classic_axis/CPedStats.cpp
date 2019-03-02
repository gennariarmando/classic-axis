#include "CGTA3D.h"
#include "CPedStats.h"

CPedStats* (&CPedStats::ms_apPedStats)[35] = *(CPedStats* (*)[35])*(int *)0x9404D4;

unsigned int CPedStats::GetPedStatType(char* pedStatName) {
	return ((unsigned int(__thiscall *)(char*))0x4EF780)(pedStatName);
}

void CPedStats::Initialise() {
	((void(__cdecl *)())0x4EF460)();
}

void CPedStats::LoadPedStats() {
	((void(__cdecl *)())0x4EF580)();
}

void CPedStats::Shutdown() {
	((void(__cdecl *)())0x4EF540)();
}
