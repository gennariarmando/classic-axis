#include "CGTA3D.h"
#include "CPlayerPed.h"
#include "CCamera.h"
#include "CWeaponEffects.h"
#include "CWorld.h"
#include "CTimer.h"
#include "Settings.h"

static CPatch InjectPatches([]() {
	if (GetSetting.bProcess_FollowPed) {
		CPatch::RedirectCall(0x4F22A0, CPlayerPed::ClearWeaponTarget);
	}
});

void __fastcall CPlayerPed::ClearWeaponTarget(CPlayerPed *_this, int) {
	if (!CPed::m_bDoAiming)
		((void(__thiscall *)(CPlayerPed *))0x4F28A0)(_this);
}

bool CPlayerPed::DoesTargetHaveToBeBroken(CVector arg0, CWeapon* weapon) {
	return ((bool(__thiscall *)(CPlayerPed *, CVector, CWeapon*))0x4F3350)(this, arg0, weapon);
}
