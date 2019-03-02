#include "CGTA3D.h"
#include "CHud.h"
#include "CWorld.h"
#include "CCamera.h"
#include "Settings.h"

float& fScreenAspectRatio = *(float *)0x5F53C0;

float GetScale(float a) {
	return static_cast<int>(a * fScreenAspectRatio);
}

void DrawCrosshair() {
	int weaponType = CWorld::Players[0].m_pPed->m_aWeapons[CWorld::Players[0].m_pPed->m_nWepSlot].m_nType;
	WORD Mode = TheCamera.Cams[TheCamera.ActiveCam].Mode;
	float x = RsGlobal.maximumWidth * TheCamera.m_f3rdPersonCHairMultX;
	float y = RsGlobal.maximumHeight * TheCamera.m_f3rdPersonCHairMultY;
	
	CSprite2d crosshair = *(CSprite2d*)0x95CBF0;

	if (!CPed::m_bHideCrosshair) {
		if (!FindPlayerVehicle() && CPed::m_bDoAiming && (Mode == MODE_FOLLOWPED) && !CPad::GetPad(0)->m_bDisablePlayerControls) {
			if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget != 1 && (weaponType >= WEAPONTYPE_COLT45 && weaponType <= WEAPONTYPE_M16) || weaponType == WEAPONTYPE_FLAMETHROWER)
				crosshair.Draw(x - GetScale(15.0f), y - GetScale(15.0f), GetScale(28.0f), GetScale(28.0f), CRGBA(255, 255, 255, 255));
		}
	}
}

static CPatch InjectPatches([]() {
	if (GetSetting.bProcess_FollowPed) {
		CPatch::Set<BYTE>(0x50554C + 1, 0);
		CPatch::Set<BYTE>(0x505627 + 1, 0);
		CPatch::RedirectCall(0x505EA9, DrawCrosshair);
	}
});
