#include "CGTA3D.h"
#include "CGeneral.h"

float CGeneral::GetATanOfXY(float x, float y) {
	return ((float(__cdecl *)(float, float))0x48CC30)(x, y);
}