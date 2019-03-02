#include "CGTAVC.h"
#include "CPedStats.h"

CPedStats* (&CPedStats::ms_apPedStats)[40] = *(CPedStats* (*)[40])*(int *)0x938828;

unsigned int CPedStats::GetPedStatType(char* pedStatName) {
	return ((unsigned int(__thiscall *)(char*))0x52FFC0)(pedStatName);
}

void CPedStats::Initialise() {
	((void(__cdecl *)())0x530260)();
}

void CPedStats::LoadPedStats() {
	((void(__cdecl *)())0x530020)();
}

void CPedStats::Shutdown() {
	((void(__cdecl *)())0x530220)();
}
