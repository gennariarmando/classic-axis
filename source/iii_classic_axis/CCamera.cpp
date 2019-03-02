#include "CGTA3D.h"
#include "CCamera.h"
#include "CSprite.h"
#include "CWorld.h"
#include "Settings.h"
#include "CTimer.h"

CCamera &TheCamera = *(CCamera *)0x6FACF8;
char &CCamera::m_nFadeColorsSet = *(char *)0x6FAD6C;
char &CCamera::m_bUseMouse3rdPerson = *(char *)0x5F03D8;

char &m_ControlMethod = *(char*)0x8F5F7C;

static CPatch InjectPatches([]() {
	CPatch::RedirectCall(0x46D500, CCamera::CamControlHook);

});

void CCamera::CamControlHook() {
	if (GetSetting.bProcess_FollowPed) {
		if (GetSetting.bForceAutoAim) {
			TheCamera.m_bUseMouse3rdPerson = false;
			m_ControlMethod = 1;
		}
		else {
			if (pXboxPad->HasPadInHands()) {
				TheCamera.m_bUseMouse3rdPerson = false;
				m_ControlMethod = 1;
			}
			else {
				TheCamera.m_bUseMouse3rdPerson = true;
				m_ControlMethod = 0;
			}
		}

		if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget != 1)
			TheCamera.CamControl();
	}
	else
		TheCamera.CamControl();

	// Focus timing.
	if ((pXboxPad->HasPadInHands() && (Pads->LookAroundLeftRight() || Pads->LookAroundUpDown())) || CPad::NewMouseControllerState.X || CPad::NewMouseControllerState.Y || (!FindPlayerVehicle() && Pads->GetTarget()))
		TheCamera.Cams->m_dwTimeToRestoreMove = CTimer::m_snTimeInMilliseconds + 1500;

	// Process our stuff here.
	if (GetSetting.bProcess_FollowPed) {
		// Manual/Auto Aiming check.
		int s = FindPlayerPed()->m_eState;
		int weaponType = CWorld::Players[0].m_pPed->m_aWeapons[CWorld::Players[0].m_pPed->m_nWepSlot].m_nType;
		if (!CPad::GetPad(0)->m_bDisablePlayerControls && !CPad::GetPad(0)->GetLookBehindForPed() && FindPlayerPed()->CanStrafeOrMouseControl() && !FindPlayerPed()->BeQuiteAndEasy() && FindPlayerPed()->m_nMoveState != PEDMOVE_SPRINT && !CPad::GetPad(0)->m_bDisablePlayerControls && !FindPlayerVehicle() && (TheCamera.Cams->Mode != MODE_TOP_DOWN_PED) && (weaponType >= WEAPONTYPE_COLT45 && weaponType <= WEAPONTYPE_FLAMETHROWER) && CPad::GetPad(0)->GetTarget())
			CPed::m_bDoAiming = true;
		else
			CPed::m_bDoAiming = false;

		if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget) {
			if ((pXboxPad->HasPadInHands() && (Pads->Mode == 4 ? (Pads->NewState.DPadDown || Pads->NewState.DPadUp || Pads->NewState.DPadLeft || Pads->NewState.DPadRight) : (Pads->LookAroundLeftRight() || Pads->LookAroundUpDown()))) || CPad::NewMouseControllerState.X || CPad::NewMouseControllerState.Y)
				((void(__thiscall *)(CPed *))0x4F28A0)(FindPlayerPed());
			//CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pPointGunAt = 0;
		}

		float fFrontalView = TheCamera.Cams->Beta - M_PI_2;

		if (TheCamera.Cams->Mode == MODE_FOLLOWPED && TheCamera.Cams->Mode != MODE_FIXED) {
			if (FindPlayerPed()->CanStrafeOrMouseControl() && !FindPlayerPed()->BeQuiteAndEasy()) {
				if (weaponType > WEAPONTYPE_UZI && weaponType < WEAPONTYPE_MOLOTOV && CPad::GetPad(0)->GetWeaponTarget()) {
					FindPlayerPed()->SetHeading(fFrontalView);

					FindPlayerPed()->m_fRotationCur = FindPlayerHeading();
					FindPlayerPed()->m_fRotationDest = FindPlayerHeading();
				}
				else if (FindPlayerPed()->CanWeRunAndFireWithWeapon() && !CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget && CPed::m_bDoAiming) {
					FindPlayerPed()->SetHeading(fFrontalView);

					FindPlayerPed()->m_fRotationCur = FindPlayerHeading();
					FindPlayerPed()->m_fRotationDest = FindPlayerHeading();
				}
				else {
					FindPlayerPed()->m_fRotationCur = FindPlayerPed()->m_fRotationCur;
					FindPlayerPed()->m_fRotationDest = FindPlayerPed()->m_fRotationDest;
				}

				FindPlayerPed()->m_matrix.UpdateRW();

				static bool m_bPointGunHasBeenCleared;
				if (!CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget) {
					if (!FindPlayerVehicle() && CPed::m_bDoAiming &&
						(weaponType >= WEAPONTYPE_COLT45 && weaponType <= WEAPONTYPE_FLAMETHROWER)) {
						FindPlayerPed()->SetAimFlag(FindPlayerPed()->m_fRotationCur);

						if (!CPad::GetPad(0)->GetWeapon() && !CPad::GetPad(0)->WeaponJustDown()) {
							FindPlayerPed()->SetPointGunAt(0);
						}

						m_bPointGunHasBeenCleared = false;
					}
					else {
						if (!m_bPointGunHasBeenCleared) {
							FindPlayerPed()->ClearPointGunAt();
							FindPlayerPed()->ClearAimFlag();
							m_bPointGunHasBeenCleared = true;
						}
					}
				}
			}
		}

		// Some hacks here to fix cycle.
		if (TheCamera.m_bUseMouse3rdPerson) {
			CPatch::Set<BYTE>(0x468D09, 0x74);
			CPatch::Set<BYTE>(0x468D92, 0x74);
		}
		else {
			CPatch::Set<BYTE>(0x468D09, 0x75);
			CPatch::Set<BYTE>(0x468D92, 0x75);
		}

		if (s == STATE_ENTERING_TRAIN || s == STATE_EXITING_TRAIN || s == STATE_GETTING_IN_VEHICLE || s == STATE_EXITING_VEHICLE || s == STATE_JACKING_VEHICLE || s == STATE_DRAGGED_OUT) {
			TheCamera.m_bCamDirectlyInFront = 0;
			TheCamera.m_bCamDirectlyBehind = 1;
		}

		// Replace settings with ours
		TheCamera.m_f3rdPersonCHairMultX = 0.5f;
		TheCamera.m_f3rdPersonCHairMultY = 0.5f;
	}
}

int CCamera::CamControl() {
	return ((int(__thiscall *)(CCamera *))_address(0x468250, 0, 0, 0, 0, 0))(this);
}

void CCamera::ClearPlayerWeaponMode() {
	return ((void(__thiscall *)(CCamera *))_address(0x46B350, 0, 0, 0, 0, 0))(this);
}

float CCamera::Find3rdPersonQuickAimPitch() {
	return ((float(__thiscall *)(CCamera *))_address(0x46B850, 0, 0, 0, 0, 0))(this);
}

int CCamera::GetLookDirection() {
	return ((int(__thiscall *)(CCamera *))_address(0x46BA50, 0, 0, 0, 0, 0))(this);
}

char CCamera::GetFading() {
	return ((char(__thiscall *)(CCamera *))_address(0x46B970, 0, 0, 0, 0, 0))(this);
}

int CCamera::GetScreenFadeStatus() {
	return ((int(__thiscall *)(CCamera *))_address(0x46B9C0, 0, 0, 0, 0, 0))(this);
}

void CCamera::SetFadeColour(char a2, char a3, int a4) {
	((void(__thiscall *)(CCamera *, char, char, char))_address(0x46FD00, 0, 0, 0, 0, 0))(this, a2, a3, a4);
}

int CCamera::Fade(float a2, int a3) {
	return ((int(__thiscall *)(CCamera *, float, int))_address(0x46B3A0, 0, 0, 0, 0, 0))(this, a2, a3);
}

int CCamera::ProcessFade() {
	return ((int(__thiscall *)(CCamera *))_address(0x46F080, 0, 0, 0, 0, 0))(this);
}

char CCamera::ProcessMusicFade() {
	return ((char(__thiscall *)(CCamera *))_address(0x46F1E0, 0, 0, 0, 0, 0))(this);
}

void __fastcall CCamera::Process(CCamera *_this, int) {
	((void(__thiscall *)(CCamera *))_address(0x52B730, 0, 0, 0, 0, 0))(_this);

}
