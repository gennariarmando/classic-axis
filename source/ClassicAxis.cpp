#include "ClassicAxis.h"
#include "Utility.h"
#include "CamNew.h"

#include "CPad.h"
#include "CGeneral.h"
#include "CCam.h"
#include "CCamera.h"
#include "CWorld.h"
#include "CSprite2d.h"
#include "CWeaponInfo.h"
#include "CMenuManager.h"
#include "CHud.h"

ClassicAxis classicAxis;

bool forceAutoAim = false;

ClassicAxis::ClassicAxis() {
	plugin::Events::initRwEvent += [] {
		GInput_Load(&classicAxis.pXboxPad);
	};
	// Patches
	auto process_FollowPedWithMouse = [](CCam* cam, int, CVector const& target, float targetOrient, float, float) {
		CCamNew* newCam = static_cast<CCamNew*>(cam);
		newCam->Process_FollowPed(target, targetOrient, 0.0f, 0.0f);
	};
	plugin::patch::RedirectCall(0x459A7C, (void(__fastcall*)(CCam*, int, CVector const&, float, float, float))process_FollowPedWithMouse);
	plugin::patch::Nop(0x459A65, 2);

	// Fps to 3rd - m16.
	plugin::patch::SetChar(0x4F1F72 + 2, -1);

	// No fight cam
	plugin::patch::Nop(0x469226, 9);
	plugin::patch::Nop(0x469260, 9);

	auto playerMovementType = [](int, int) {
		int moveType = TYPE_WALKAROUND;

		if (classicAxis.isAiming)
			moveType = TYPE_STRAFE;

		return moveType;
	};

	int playerMovementTypeAddr[] = { 0x4F2685, 0x469292, 0x4C7673, 0x4F03D5, 0x4D76CE, 0x45DB98 };
	for (int i = 0; i < 6; i++)
		plugin::patch::RedirectCall(playerMovementTypeAddr[i], (int(__fastcall*)(int, int))playerMovementType);

	auto playerShootingDirection = [](int, int) {
		int moveType = TYPE_WALKAROUND;

		if (classicAxis.isAiming && !CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget)
			moveType = TYPE_STRAFE;

		return moveType;
	};

	int playerShootingDirectionAddr[] = { 0x4E6562, 0x55D88B, 0x560C25 };
	for (int i = 0; i < 3; i++)
		plugin::patch::RedirectCall(playerShootingDirectionAddr[i], (int(__fastcall*)(int, int))playerShootingDirection);

	auto zero = []() { };
	plugin::patch::RedirectCall(0x468E46, (void(__cdecl*)())zero);

	plugin::patch::Nop(0x4F21A0, 6);
	plugin::patch::Nop(0x4F21CA, 7);

	auto camControl = [](int, int) {
		TheCamera.m_bUseMouse3rdPerson = true;
		FrontEndMenuManager.m_ControlMethod = 0;
	
		if (!CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget)
			TheCamera.CamControl();

		CPlayerPed* playa = FindPlayerPed();
		CPad* pad = CPad::GetPad(0);
		CCam cam = TheCamera.m_asCams[TheCamera.m_nActiveCam];
		char Mode = cam.m_nCamMode;
		float front = CGeneral::LimitRadianAngle(-TheCamera.m_fOrientation);
		eWeaponState state = playa->m_aWeapons[playa->m_nCurrentWeapon].m_eWeaponState;

		classicAxis.isAiming = false;
		if (playa && pad && !classicAxis.WaitOrAim(playa) && classicAxis.IsWeaponPossiblyCompatible(playa) && pad->GetTarget()) {
			classicAxis.isAiming = true;

			CEntity* p = playa->m_pPointGunAt;
			if (playa->m_bHasLockOnTarget && p) {
				front = CGeneral::GetATanOfXY(cam.m_vecSource.x - p->GetPosition().x, cam.m_vecSource.y - p->GetPosition().y) + M_PI_2;

				if ((classicAxis.pXboxPad->HasPadInHands() &&
					(pad->m_nMode == 4 ? pad->NewState.LeftShoulder2 <= 30 /*(Pads->NewState.DPadDown || Pads->NewState.DPadUp || Pads->NewState.DPadLeft || Pads->NewState.DPadRight)*/ : (pad->LookAroundLeftRight() || pad->LookAroundUpDown()))) || CPad::NewMouseControllerState.X || CPad::NewMouseControllerState.Y)
					playa->ClearWeaponTarget();
			}
			else {
				if (/*!pad->SecondaryFireJustDown() && */(pad->m_nMode == 4 ? pad->NewState.LeftShoulder2 >= 30 : pad->ShiftTargetLeftJustDown() || pad->ShiftTargetRightJustDown()))
					playa->FindWeaponLockOnTarget();
			}

			playa->m_fRotationCur = front;
			playa->m_fRotationDest = front;

			playa->m_matrix.SetRotateZOnly(FindPlayerPed()->m_fRotationCur);

			playa->SetLookFlag(front, false);
			playa->SetAimFlag(front);

			if (!playa->m_bHasLockOnTarget)
				playa->m_fFPSMoveHeading = TheCamera.Find3rdPersonQuickAimPitch() * 0.75f;

			if (!pad->GetWeapon()) {
				playa->SetPointGunAt(NULL);
				classicAxis.wasPointing = true;
			}
		}

		if (!classicAxis.isAiming) {
			if (classicAxis.wasPointing) {
				playa->ClearPointGunAt();
				classicAxis.wasPointing = false;
			}
		}
	};

	plugin::patch::RedirectCall(0x46D500, (void(__fastcall*)(int, int))camControl);

	// Crosshair
	auto drawCrosshair = []() {
		CCam cam = TheCamera.m_asCams[TheCamera.m_nActiveCam];
		CPlayerPed* playa = FindPlayerPed();
		CPad* pad = CPad::GetPad(0);

		if (!playa)
			return;

		if (!pad)
			return;

		const eWeaponType weaponType = playa->m_aWeapons[playa->m_nCurrentWeapon].m_eWeaponType;
		char Mode = cam.m_nCamMode;
		float x = RsGlobal.maximumWidth * TheCamera.m_f3rdPersonCHairMultX;
		float y = RsGlobal.maximumHeight * TheCamera.m_f3rdPersonCHairMultY;

		CWeaponInfo* info = CWeaponInfo::GetWeaponInfo(weaponType);
		eWeaponState state = playa->m_aWeapons[playa->m_nCurrentWeapon].m_eWeaponState;

		CSprite2d* crosshair = &CHud::Sprites[HUD_SITEM16];
		if (crosshair && crosshair->m_pTexture) {
			if (classicAxis.isAiming) {
				if (!playa->m_pVehicle && Mode == 4 && !CPad::GetPad(0)->m_bDisablePlayerControls) {
					if (!playa->m_bHasLockOnTarget && (weaponType >= WEAPONTYPE_COLT45 && weaponType <= WEAPONTYPE_M16) || weaponType == WEAPONTYPE_FLAMETHROWER)
						crosshair->Draw(CRect(x - Scale(22.0f), y - Scale(22.0f), x + Scale(22.0f), y + Scale(22.0f)), CRGBA(255, 255, 255, 255));
				}

			}
		}
	};
	plugin::patch::SetChar(0x50554C + 1, 0);
	plugin::patch::SetChar(0x505627 + 1, 0);
	plugin::patch::RedirectCall(0x505EA9, (void(__cdecl*)())drawCrosshair);

	// No rotate torso
	plugin::patch::PutRetn(0x4EDDB0);

	// Menu
	const CMenuScreen controllerSetup = {
		"FET_CTL", 41, 41, 41, 0, 0,
		MENUACTION_REDEFCTRL, "FET_RDK",  0,  MENUPAGE_KEYBOARD_CONTROLS,
		MENUACTION_CHANGEMENU, "FET_AMS", 0,  MENUPAGE_MOUSE_CONTROLS,
		MENUACTION_RESTOREDEF, "FET_DEF", 0,  MENUPAGE_CONTROLLER_PC,
		MENUACTION_CHANGEMENU, "FEDS_TB", 0,  MENUPAGE_NONE,
	};
	
	plugin::patch::Set(0x611930 + sizeof(CMenuScreen) * 35, controllerSetup);
	
	// Weapon cycle
	auto processWeaponSwitch = [](CPlayerPed* ped, int, CPad* pad) {
		if (!classicAxis.isAiming)
			return ped->ProcessWeaponSwitch(pad);
	
		return;
	};
	plugin::patch::RedirectCall(0x4F0464, (void(__fastcall*)(CPlayerPed*, int, CPad*))processWeaponSwitch);
}

bool ClassicAxis::WaitOrAim(CPed* ped) {
	ePedState s = ped->m_ePedState;
	eMoveState m = ped->m_eMoveState;

	return m == PEDMOVE_SPRINT || 
		(s >= PEDSTATE_JUMP && s <= PEDSTATE_DRIVING) || 
		(s == PEDSTATE_SEEK_CAR || s == PEDSTATE_SEEK_IN_BOAT || s == PEDSTATE_GETUP || s == PEDSTATE_ON_FIRE);
}

bool ClassicAxis::IsWeaponPossiblyCompatible(CPed* ped) {
	const eWeaponType weaponType = ped->m_aWeapons[ped->m_nCurrentWeapon].m_eWeaponType;
	eWeaponFire info = CWeaponInfo::GetWeaponInfo(weaponType)->m_eWeaponFire;

	switch (weaponType) {
	case WEAPONTYPE_SNIPERRIFLE:
		return false;
	}

	return info == WEAPON_FIRE_AREA_EFFECT || info == WEAPON_FIRE_INSTANT_HIT;
}
