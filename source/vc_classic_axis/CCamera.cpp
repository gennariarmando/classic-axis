#include "CGTAVC.h"
#include "CCamera.h"
#include "CSprite.h"
#include "CWorld.h"
#include "Settings.h"
#include "CTimer.h"
#include "CGeneral.h"
#include "CWeaponInfo.h"

CCamera &TheCamera = *(CCamera *)0x7E4688;
char &CCamera::m_nFadeColorsSet = *(char *)0x6FAD6C;
char &CCamera::m_bUseMouse3rdPerson = *(char *)0xA10B4C;
float &CCamera::m_f3rdPersonCHairMultX = *(float*)0xA0D91C;
float &CCamera::m_f3rdPersonCHairMultY = *(float*)0xA0D924;
float &CCamera::m_fMouseAccelVertical = *(float*)0xA0D964;
float &CCamera::m_fMouseAccelHorzntl = *(float*)0x94DBD0;

char &m_ControlMethod = *(char*)0x86968B;
bool CCamera::CCamera::m_bWalkSideways;

static CPatch InjectPatches([]() {
	CPatch::RedirectCall(0x46C694, CCamera::CamControlHook);
});

void CCamera::CamControlHook() {
	if (GetSetting.bProcess_FollowPed) {
		if (GetSetting.bForceAutoAim) {
			m_bUseMouse3rdPerson = false;
			m_ControlMethod = 1;
		}
		else {
			if (pXboxPad->HasPadInHands()) {
				m_bUseMouse3rdPerson = false;
				m_ControlMethod = 1;
			}
			else {
				m_bUseMouse3rdPerson = true;
				m_ControlMethod = 0;
			}
		}

		if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget != 1)
			TheCamera.CamControl();
	}
	else
		TheCamera.CamControl();

	TheCamera.ProcessClassicAxis();
}

void CCamera::ProcessClassicAxis() {
	CCam* Cams = TheCamera.Cams;

	// Focus timing.
	if (Cams->LookingBehind && Cams->LookingLeft && Cams->LookingRight) {}
	else {
		if ((pXboxPad->HasPadInHands() && (Pads->LookAroundLeftRight() || Pads->LookAroundUpDown())) || CPad::NewMouseControllerState.X || CPad::NewMouseControllerState.Y || (!FindPlayerVehicle() && Pads->GetTarget()))
			Cams->m_dwTimeToRestoreMove = CTimer::m_snTimeInMilliseconds + 1500;
	}

	// Process our stuff here.
	static bool m_bPointGunHasBeenCleared;
	if (GetSetting.bProcess_FollowPed) {
		// Manual/Auto Aiming check.
		int s = FindPlayerPed()->m_eState;
		int weaponType = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_aWeapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_nWepSlot].m_nType;
		if (!Pads->GetLookBehindForPed() && FindPlayerPed()->CanStrafeOrMouseControl() && !FindPlayerPed()->BeQuiteAndEasy() && FindPlayerPed()->m_nMoveState != PEDMOVE_SPRINT && !FindPlayerVehicle() && (Cams->Mode != MODE_TOP_DOWN_PED) && (!FindPlayerPed()->IsTypeMelee()) && Pads->GetTarget())
			CPed::m_bDoAiming = true;
		else
			CPed::m_bDoAiming = false;

		if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget) {
			if ((pXboxPad->HasPadInHands() && (Pads->Mode == 4 ? Pads->NewState.LeftShoulder2 <= 30 /*(Pads->NewState.DPadDown || Pads->NewState.DPadUp || Pads->NewState.DPadLeft || Pads->NewState.DPadRight)*/ : (Pads->LookAroundLeftRight() || Pads->LookAroundUpDown()))) || CPad::NewMouseControllerState.X || CPad::NewMouseControllerState.Y)
				((void(__thiscall *)(CPed *))0x533B30)(FindPlayerPed());
		}
		else {
			if (CPed::m_bDoAiming) {
				if (!Pads->SecondaryFireJustDown() && (Pads->Mode == 4 ? Pads->NewState.LeftShoulder2 >= 30 : Pads->ShiftTargetLeftJustDown() || Pads->ShiftTargetRightJustDown()))
					((void(__thiscall *)(CPed *))0x533030)(FindPlayerPed());
			}
		}

		float fFrontalView = CGeneral::GetATanOfXY(Cams->Front.x, Cams->Front.y) - M_PI_2;

		if (!Pads->m_bDisablePlayerControls && !FindPlayerPed()->IsTypeMelee() && !CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget && Cams->Mode == MODE_FOLLOWPED || Cams->Mode == MODE_1STPERSON || Cams->Mode == MODE_ROCKETLAUNCHER || Cams->Mode == MODE_SNIPER || Cams->Mode == MODE_M16_1STPERSON) {
			if (FindPlayerPed()->CanStrafeOrMouseControl() && !FindPlayerPed()->BeQuiteAndEasy()) {
				if (Pads->GetWeapon() && !FindPlayerPed()->CanWeRunAndFireWithWeapon() && !FindPlayerPed()->FirstPersonWeapons()) {
					FindPlayerPed()->SetAimFlag(FindPlayerPed()->m_fRotationCur);
					FindPlayerPed()->m_placement.SetHeading(fFrontalView);

					FindPlayerPed()->m_fRotationCur = FindPlayerHeading();
					FindPlayerPed()->m_fRotationDest = FindPlayerHeading();
					CCamera::m_bWalkSideways = true;
				}
				else if (CPed::m_bDoAiming) {
					FindPlayerPed()->SetAimFlag(FindPlayerPed()->m_fRotationCur);
					FindPlayerPed()->m_placement.SetHeading(fFrontalView);

					FindPlayerPed()->m_fRotationCur = FindPlayerHeading();
					FindPlayerPed()->m_fRotationDest = FindPlayerHeading();
					CCamera::m_bWalkSideways = true;
				}
				else {
					FindPlayerPed()->m_fRotationCur = FindPlayerPed()->m_fRotationCur;
					FindPlayerPed()->m_fRotationDest = FindPlayerPed()->m_fRotationDest;
					CCamera::m_bWalkSideways = false;
				}

				FindPlayerPed()->m_placement.UpdateRW();
			}

			if (CPed::m_bDoAiming && !FindPlayerPed()->FirstPersonWeapons() && s != STATE_ATTACK && s != STATE_FIGHT && s != STATE_FACE_PHONE && s != STATE_MAKE_PHONECALL && !Pads->DuckJustDown()) {			
				FindPlayerPed()->SetPointGunAt(0);

				m_bPointGunHasBeenCleared = false;
			}
			else {
				if (!m_bPointGunHasBeenCleared) {
					FindPlayerPed()->ClearPointGunAt();
					FindPlayerPed()->ClearAimFlag();

					m_bPointGunHasBeenCleared = true;
				}

				// Duck temporary fix.
				if (FindPlayerPed()->m_dwDuckTimer)
					FindPlayerPed()->SetDuck(60000, 1);
			}
		}
		else {
			m_bPointGunHasBeenCleared = false;
			CCamera::m_bWalkSideways = false;
		}

		// Chainsaw temporary fix.
		if (weaponType == WEAPONTYPE_CHAINSAW && Pads->GetWeapon() && FindPlayerPed() && FindPlayerPed()->m_fTotSpeed >= 0.06f) {
			FindPlayerPed()->m_placement.SetRotateZOnly(fFrontalView);
			FindPlayerPed()->m_fRotationCur = fFrontalView;
			FindPlayerPed()->m_fRotationDest = fFrontalView;
		}

		// Some hacks here.
		// Fix cycle.
		if (m_bUseMouse3rdPerson) {
			CPatch::Set<BYTE>(0x471093, 0x74);
			CPatch::Set<BYTE>(0x47111B, 0x74);
		}
		else {
			CPatch::Set<BYTE>(0x471093, 0x75);
			CPatch::Set<BYTE>(0x47111B, 0x75);
		}

		// Restore aiming point in case "Widescreen Fix" changes it.
		CPatch::SetPointer(0x46F925 + 2, &m_f3rdPersonCHairMultX);
		
		// No jump while aiming.
		if (CPed::m_bDoAiming)
			CPatch::Set<BYTE>(0x4F03CA, 0x74);
		else
			CPatch::Set<BYTE>(0x4F03CA, 0x75);

		// Replace settings with ours
		m_f3rdPersonCHairMultX = 0.5f;
		m_f3rdPersonCHairMultY = 0.5f;
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
