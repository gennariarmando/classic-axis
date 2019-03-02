#include "CGTAVC.h"
#include "CGeneral.h"

float CGeneral::GetATanOfXY(float x, float y) {
	return ((float(__cdecl *)(float, float))0x4A55E0)(x, y);
}