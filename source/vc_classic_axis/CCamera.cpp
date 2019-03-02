#include "CGTAVC.h"
#include "CCamera.h"
#include "CSprite.h"
#include "CWorld.h"
#include "Settings.h"
#include "CTimer.h"

CCamera &TheCamera = *(CCamera *)0x7E4688;
char &CCamera::m_nFadeColorsSet = *(char *)0x6FAD6C;
char &CCamera::m_bUseMouse3rdPerson = *(char *)0xA10B4C;
float &CCamera::m_f3rdPersonCHairMultX = *(float*)0xA0D91C;
float &CCamera::m_f3rdPersonCHairMultY = *(float*)0xA0D924;
float &CCamera::m_fMouseAccelVertical = *(float*)0xA0D964;
float &CCamera::m_fMouseAccelHorzntl = *(float*)0x94DBD0;

char &m_ControlMethod = *(char*)0x86968B;

static CPatch InjectPatches([]() {
	CPatch::RedirectCall(0x46C694, CCamera::CamControlHook);
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
	int DisableControls = CPad::GetPad(0)->m_bDisablePlayerControls & 0x20;
	if ((pXboxPad->HasPadInHands() && (Pads->LookAroundLeftRight() || Pads->LookAroundUpDown())) || CPad::NewMouseControllerState.X || CPad::NewMouseControllerState.Y || (!FindPlayerVehicle() && Pads->GetTarget()))
		TheCamera.Cams[TheCamera.ActiveCam].m_dwTimeToRestoreMove = CTimer::m_snTimeInMilliseconds + 1500;

	// Process our stuff here.
	if (GetSetting.bProcess_FollowPed) {
		// Manual/Auto Aiming check.
		int s = FindPlayerPed()->m_eState;
		int weaponType = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_aWeapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_nWepSlot].m_nType;
		if ((!DisableControls) && !CPad::GetPad(0)->GetLookBehindForPed() && FindPlayerPed()->CanStrafeOrMouseControl() && !FindPlayerPed()->BeQuiteAndEasy() && FindPlayerPed()->m_nMoveState != PEDMOVE_SPRINT && !FindPlayerVehicle() && (TheCamera.Cams[TheCamera.ActiveCam].Mode != MODE_TOP_DOWN_PED) && (weaponType >= WEAPONTYPE_PISTOL && weaponType <= WEAPONTYPE_MINIGUN) && CPad::GetPad(0)->GetTarget())
			CPed::m_bDoAiming = true;
		else
			CPed::m_bDoAiming = false;

		if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget) {
			if ((pXboxPad->HasPadInHands() && (Pads->Mode == 4 ? (Pads->NewState.DPadDown || Pads->NewState.DPadUp || Pads->NewState.DPadLeft || Pads->NewState.DPadRight) : (Pads->LookAroundLeftRight() || Pads->LookAroundUpDown()))) || CPad::NewMouseControllerState.X || CPad::NewMouseControllerState.Y)
				((void(__thiscall *)(CPed *))0x533B30)(FindPlayerPed());
			//CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pPointGunAt = 0;
		}

		float fFrontalView = TheCamera.Cams[TheCamera.ActiveCam].Beta - M_PI_2;

		if (!CPad::GetPad(0)->m_bDisablePlayerControls && TheCamera.Cams[TheCamera.ActiveCam].Mode == MODE_FOLLOWPED && TheCamera.Cams[TheCamera.ActiveCam].Mode != MODE_FIXED) {
			if (FindPlayerPed()->CanStrafeOrMouseControl() && !FindPlayerPed()->BeQuiteAndEasy()) {
				if (FindPlayerPed()->HeavyWeapons() && CPad::GetPad(0)->GetWeaponTarget() || CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_aWeapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_nWepSlot].m_nType == WEAPONTYPE_CHAINSAW && CPad::GetPad(0)->GetWeapon()) {
					FindPlayerPed()->m_placement.SetHeading(fFrontalView);

					FindPlayerPed()->m_fRotationCur = FindPlayerHeading();
					FindPlayerPed()->m_fRotationDest = FindPlayerHeading();
				}
				else if (FindPlayerPed()->CanWeRunAndFireWithWeapon() && !CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget && CPed::m_bDoAiming) {
					FindPlayerPed()->m_placement.SetHeading(fFrontalView);

					FindPlayerPed()->m_fRotationCur = FindPlayerHeading();
					FindPlayerPed()->m_fRotationDest = FindPlayerHeading();
				}
				else {
					FindPlayerPed()->m_fRotationCur = FindPlayerPed()->m_fRotationCur;
					FindPlayerPed()->m_fRotationDest = FindPlayerPed()->m_fRotationDest;
				}

				FindPlayerPed()->m_placement.UpdateRW();

				static bool m_bPointGunHasBeenCleared;
				if (!CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget) {
					if (!FindPlayerVehicle() && CPed::m_bDoAiming &&
						(weaponType >= WEAPONTYPE_PISTOL && weaponType <= WEAPONTYPE_MINIGUN)) {
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
							FindPlayerPed()->ClearAll();
							m_bPointGunHasBeenCleared = true;
						}
					}
				}
			}
		}

		// Some hacks here.
		// Fix cycle.
		if (TheCamera.m_bUseMouse3rdPerson) {
			CPatch::Set<BYTE>(0x471093, 0x74);
			CPatch::Set<BYTE>(0x47111B, 0x74);
		}
		else {
			CPatch::Set<BYTE>(0x471093, 0x75);
			CPatch::Set<BYTE>(0x47111B, 0x75);
		}

		// Restore aiming point in case "Widescreen Fix" breaks it.
		CPatch::SetPointer(0x46F925 + 2, &TheCamera.m_f3rdPersonCHairMultX);

		if (s == STATE_ENTERING_TRAIN || s == STATE_GETTING_IN_VEHICLE || s == STATE_JACKING_VEHICLE) {
			TheCamera.Cams->m_fTransitionBeta = 0.0f;
		}
		else if (s == STATE_EXITING_TRAIN || s == STATE_EXITING_VEHICLE || s == STATE_DRAGGED_OUT) {
			TheCamera.m_bCamDirectlyBehind = true;
		}

		// Replace settings with ours
		TheCamera.m_f3rdPersonCHairMultX = 0.5f;
		TheCamera.m_f3rdPersonCHairMultY = 0.5f;
	}
}

int CCamera::CamControl() {
	return ((int(__thiscall *)(CCamera *))(0x4700E7))(this);
}

void CCamera::ClearPlayerWeaponMode() {
	return ((void(__thiscall *)(CCamera *))0x46FE51)(this);
}

float CCamera::Find3rdPersonQuickAimPitch() {
	return ((float(__thiscall *)(CCamera *))0x46F7C6)(this);
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
