#include "CGTA3D.h"
#include "CPlaceable.h"


// Converted from thiscall void CPlaceable::CPlaceable(void) 0x49F9A0
CPlaceable::CPlaceable() : m_matrix() {
	((void(__thiscall *)(CPlaceable*))0x49F9A0)(this);
}

// Converted from thiscall bool CPlaceable::IsWithinArea(float x1,float y1,float z1,float x2,float y2,float z2) 0x49FAF0
bool CPlaceable::IsWithinArea(float x1, float y1, float z1, float x2, float y2, float z2) {
	return ((bool(__thiscall *)(CPlaceable*, float, float, float, float, float, float))0x49FAF0)(this, x1, y1, z1, x2, y2, z2);
}

// Converted from thiscall bool CPlaceable::IsWithinArea(float x1,float y1,float x2,float y2) 0x49FA50
bool CPlaceable::IsWithinArea(float x1, float y1, float x2, float y2) {
	return ((bool(__thiscall *)(CPlaceable*, float, float, float, float))0x49FA50)(this, x1, y1, x2, y2);
}

// Converted from thiscall void CPlaceable::SetHeading(float heading) 0x49FA00
void CPlaceable::SetHeading(float heading) {
	((void(__thiscall *)(CPlaceable*, float))0x49FA00)(this, heading);
}

// Converted from thiscall void CPlaceable::~CPlaceable(void) 0x49F9E0
CPlaceable::~CPlaceable() {
	((void(__thiscall *)(CPlaceable*))0x49F9E0)(this);
}
