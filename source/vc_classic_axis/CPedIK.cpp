#include "CGTAVC.h"
#include "CPedIK.h"
#include "Settings.h"

RwMatrix* CPedIK::GetComponentPosition(RwV3d* pos, int id) {
	return ((RwMatrix*(__thiscall *)(CPedIK *, RwV3d*, int))0x4ED0F0)(this, pos, id);
}

char CPedIK::PointGunInDirection(float phi, float theta) {
	return ((char(__thiscall *)(CPedIK *, float, float))0x4ED9B0)(this, phi, theta);
}

char CPedIK::PointGunAtPosition(CVector const& posn) {
	return ((char(__thiscall *)(CPedIK *, CVector const&))0x4ED920)(this, posn);
}
