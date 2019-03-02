#include "CGTAVC.h"
#include "CHud.h"
#include "CWorld.h"
#include "CCamera.h"
#include "Settings.h"

float& fScreenAspectRatio = *(float *)0x94DD38;

float GetScale(float a) {
	return static_cast<int>(a * fScreenAspectRatio);
}

void DrawCrosshair() {
	int weaponType = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_aWeapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_nWepSlot].m_nType;
	WORD Mode = TheCamera.Cams[TheCamera.ActiveCam].Mode;
	float x = RsGlobal.maximumWidth * TheCamera.m_f3rdPersonCHairMultX;
	float y = RsGlobal.maximumHeight * TheCamera.m_f3rdPersonCHairMultY;
	
	CSprite2d *crosshair = (CSprite2d*)0xA10844;

	if (!CPed::m_bHideCrosshair) {
		if (!FindPlayerVehicle() && CPed::m_bDoAiming && (Mode == MODE_FOLLOWPED) && !CPad::GetPad(0)->m_bDisablePlayerControls) {
			if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget != 1 && (weaponType >= WEAPONTYPE_PISTOL && weaponType <= WEAPONTYPE_RUGER) || weaponType == WEAPONTYPE_FLAMETHROWER || weaponType == WEAPONTYPE_M60 || weaponType == WEAPONTYPE_MINIGUN)
				crosshair->Draw(x - GetScale(15.0f), y - GetScale(15.0f), GetScale(28.0f), GetScale(28.0f), CRGBA(255, 255, 255, 255));
		}
	}
}
void __fastcall test(int _this, int, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11) { }
static CPatch InjectPatches([]() {
	if (GetSetting.bProcess_FollowPed) {
		CPatch::RedirectCall(0x557713, test);
		CPatch::RedirectCall(0x5577F7, test);

		CPatch::RedirectCall(0x5581C4, DrawCrosshair);
	}
});
