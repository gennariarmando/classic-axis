#include "CGTAVC.h"
#include "CPlayerPed.h"
#include "CCamera.h"
#include "CWeaponEffects.h"
#include "CWorld.h"
#include "CTimer.h"
#include "Settings.h"

bool CPlayerPed::DoesTargetHaveToBeBroken(CVector arg0, CWeapon* weapon) {
	return ((bool(__thiscall *)(CPlayerPed *, CVector, CWeapon*))0x00)(this, arg0, weapon);
}
