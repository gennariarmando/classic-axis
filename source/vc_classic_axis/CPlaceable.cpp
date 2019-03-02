#include "CGTAVC.h"
#include "CPlaceable.h"

CPlaceable::CPlaceable() : CMatrix() {
	((void(__thiscall *)(CPlaceable*))0x4BBAD0)(this);
}

bool CPlaceable::IsWithinArea(float x1, float y1, float z1, float x2, float y2, float z2) {
	return ((bool(__thiscall *)(CPlaceable*, float, float, float, float, float, float))0x4BB900)(this, x1, y1, z1, x2, y2, z2);
}

bool CPlaceable::IsWithinArea(float x1, float y1, float x2, float y2) {
	return ((bool(__thiscall *)(CPlaceable*, float, float, float, float))0x4BB9E0)(this, x1, y1, x2, y2);
}

void CPlaceable::SetHeading(float heading) {
	((void(__thiscall *)(CPlaceable*, float))0x4BBA80)(this, heading);
}

void CPlaceable::SetOrientation(float x, float y, float z) {
	CVector currPos = this->pos;
	this->SetRotate(x, y, z);
	this->pos = currPos;
}

void CPlaceable::GetOrientation(float& x, float& y, float& z) {
	x = asinf(this->up.z);
	float cosx = cosf(x);
	float cosy = this->at.z / cosx;
	y = acosf(cosy);
	float cosz = this->up.y / cosx;
	z = acosf(cosz);
}