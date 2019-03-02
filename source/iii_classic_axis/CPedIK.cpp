#include "CGTA3D.h"
#include "CPedIK.h"
#include "Settings.h"

LimbMovementInfo *CPedIK::ms_headInfo = (LimbMovementInfo *)0x5F9F5C;
LimbMovementInfo *CPedIK::ms_headRestoreInfo = (LimbMovementInfo *)0x5F9F74;
LimbMovementInfo *CPedIK::ms_torsoInfo = (LimbMovementInfo *)0x5F9F8C;
LimbMovementInfo *CPedIK::ms_upperArmInfo = (LimbMovementInfo *)0x5F9FA4;
LimbMovementInfo *CPedIK::ms_lowerArmInfo = (LimbMovementInfo *)0x5F9FBC;

static CPatch InjectPatches([]() {
	if (GetSetting.bTorsoFix)
		CPatch::RedirectJump(0x4EDDB0, CPedIK::RotateTorso);
});

void __fastcall CPedIK::RotateTorso(void *, int, int, int, char) {

}

RwMatrix* CPedIK::GetComponentPosition(RwV3d* pos, int id) {
	return ((RwMatrix*(__thiscall *)(CPedIK *, RwV3d*, int))0x4ED0F0)(this, pos, id);
}

char CPedIK::PointGunInDirection(float phi, float theta) {
	return ((char(__thiscall *)(CPedIK *, float, float))0x4ED9B0)(this, phi, theta);
}

char CPedIK::PointGunAtPosition(CVector const& posn) {
	return ((char(__thiscall *)(CPedIK *, CVector const&))0x4ED920)(this, posn);
}
