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
		classicAxis.isAiming = false;
		classicAxis.wasPointing = false;
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

	int playerShootingDirectionAddr[] = { 0x4E6562, 0x55D88B, 0x560C25, 0x561E63, 0x4EDAD1 };
	for (int i = 0; i < 5; i++)
		plugin::patch::RedirectCall(playerShootingDirectionAddr[i], (int(__fastcall*)(int, int))playerShootingDirection);

	auto zero = []() { };
	plugin::patch::RedirectCall(0x468E46, (void(__cdecl*)())zero);

	auto clearWeaponTarget = [](CPlayerPed* playa, int) {
		if (!classicAxis.isAiming)
			playa->ClearWeaponTarget();
	};
	plugin::patch::RedirectCall(0x4F22A0, (void(__fastcall*)(CPlayerPed*, int))clearWeaponTarget);

	plugin::patch::Nop(0x4F21A0, 6);
	plugin::patch::Nop(0x4F21CA, 7);

	plugin::patch::Set<BYTE>(0x468D09, 0x74);
	plugin::patch::Set<BYTE>(0x468D92, 0x74);

	auto camControl = [](int, int) {
		TheCamera.m_bUseMouse3rdPerson = true;
		FrontEndMenuManager.m_ControlMethod = 0;
		//TheCamera.m_f3rdPersonCHairMultX = 0.5f;
		//TheCamera.m_f3rdPersonCHairMultY = 0.5f;

		if (!CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget)
			TheCamera.CamControl();

		CPlayerPed* playa = FindPlayerPed();
		CPad* pad = CPad::GetPad(0);
		CCam cam = TheCamera.m_asCams[TheCamera.m_nActiveCam];
		char Mode = cam.m_nCamMode;
		float front = CGeneral::LimitRadianAngle(-TheCamera.m_fOrientation);
		eWeaponState state = playa->m_aWeapons[playa->m_nCurrentWeapon].m_eWeaponState;
		const eWeaponType weaponType = playa->m_aWeapons[playa->m_nCurrentWeapon].m_eWeaponType;
		CWeaponInfo* info = CWeaponInfo::GetWeaponInfo(weaponType);

		classicAxis.isAiming = false;

		if (playa && pad && classicAxis.IsAbleToAim(playa) && classicAxis.IsWeaponPossiblyCompatible(playa) && pad->GetTarget() && TheCamera.GetLookDirection() != 0) {
			classicAxis.isAiming = true;

			CEntity* p = playa->m_pPointGunAt;
			float mouseX = CPad::GetPad(0)->NewMouseControllerState.X;
			float mouseY = CPad::GetPad(0)->NewMouseControllerState.Y;

			if (playa->m_bHasLockOnTarget && p) {
				front = CGeneral::GetATanOfXY(cam.m_vecSource.x - p->GetPosition().x, cam.m_vecSource.y - p->GetPosition().y) + M_PI_2;

				if ((classicAxis.pXboxPad->HasPadInHands() &&
					(pad->m_nMode == 4 ? pad->NewState.LeftShoulder2 <= 30 : (pad->LookAroundLeftRight() || pad->LookAroundUpDown()))) || (abs(mouseX) > 1.0f || abs(mouseY) > 1.0f))
					playa->ClearWeaponTarget();
			}
			else {
				if (/*!pad->SecondaryFireJustDown() && */(pad->m_nMode == 4 ? pad->NewState.LeftShoulder2 >= 30 : pad->ShiftTargetLeftJustDown() || pad->ShiftTargetRightJustDown()))
					playa->FindWeaponLockOnTarget();
			}

			playa->m_fRotationCur = front;
			playa->m_fRotationDest = front;

			playa->m_matrix.SetRotateZOnly(playa->m_fRotationCur);

			playa->m_nLookTimer = 0;
			playa->SetLookFlag(front, false);
			playa->SetAimFlag(front);

			if (!playa->m_bHasLockOnTarget)
				playa->m_fFPSMoveHeading = interpF(playa->m_fFPSMoveHeading, TheCamera.Find3rdPersonQuickAimPitch(), 0.2f * CTimer::ms_fTimeStep);

			playa->m_fFPSMoveHeading = clamp(playa->m_fFPSMoveHeading, DegToRad(-40.0f), DegToRad(40.0f));

			CAnimBlendAssociation* anim = plugin::CallAndReturn<CAnimBlendAssociation*, 0x4055C0>(playa->m_pRwClump, info->m_AnimToPlay);
			bool point = true;
			if (anim && (anim->m_fCurrentTime < info->m_fAnimLoopEnd)) {
				point = false;
			}

			if (pad->GetWeapon())
				point = false;

			if (point) {
				playa->SetPointGunAt(NULL);
				classicAxis.wasPointing = true;
			}
		}

		if (!classicAxis.isAiming) {
			if (playa) {
				if (classicAxis.wasPointing && playa->m_ePedState != PEDSTATE_ATTACK) {
					playa->ClearPointGunAt();
					playa->ClearWeaponTarget();
					classicAxis.wasPointing = false;
				}

				if (pad->GetWeapon() && classicAxis.IsAbleToAim(playa) && !classicAxis.IsTypeMelee(playa) && !info->m_bCanAimWithArm && !info->m_bThrow && !info->m_bHeavy && !info->m_b1stPerson) {
					playa->m_fRotationDest = front;
					playa->m_fRotationCur = CGeneral::LimitRadianAngle(playa->m_fRotationCur);
					float angle = playa->m_fRotationDest;

					if (playa->m_fRotationCur - M_PI > playa->m_fRotationDest) {
						angle += 2 * M_PI;
					}
					else if (M_PI + playa->m_fRotationCur < playa->m_fRotationDest) {
						angle -= 2 * M_PI;
					}

					playa->m_fRotationCur += (angle - playa->m_fRotationCur) * 0.5f;
				}
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
		if (crosshair) {
			if (classicAxis.isAiming) {
				if (!playa->m_bInVehicle && Mode == 4 && !CPad::GetPad(0)->m_bDisablePlayerControls) {
					if (!playa->m_bHasLockOnTarget && (weaponType >= WEAPONTYPE_COLT45 && weaponType <= WEAPONTYPE_M16) || weaponType == WEAPONTYPE_FLAMETHROWER)
						crosshair->Draw(CRect(x - Scale(22.0f), y - Scale(22.0f), x + Scale(22.0f), y + Scale(22.0f)), CRGBA(255, 255, 255, 255));
				}

			}
		}
	};
	plugin::patch::SetChar(0x50554C + 1, 0);
	plugin::patch::SetChar(0x505627 + 1, 0);
	plugin::Events::drawHudEvent += drawCrosshair;

	// Draw marker
	auto drawAutoAimCrosshair = [](float x, float y, float z, float w, float h, unsigned __int8 r, unsigned __int8 g, unsigned __int8 b, __int16 intens, float recipz, unsigned __int8 a) {
		CPed* playa = FindPlayerPed();
		CEntity* e = playa->m_pPointGunAt;
		if (!playa && !e)
			return;

		float health = static_cast<CPed*>(e)->m_fHealth / 100.0f;
		CRGBA col = CRGBA((1.0f - health) * 255, health * 255, 0, 255);
		if (health <= 0.0f)
			col = CRGBA(0, 0, 0, 255);

		y -= 6.0f;
		DrawTarget(x, y - (h / 2), (w / 128.0f), col);
	};
	plugin::patch::RedirectCall(0x564E3E, (void(__cdecl*)(float, float, float, float, float, unsigned __int8, unsigned __int8, unsigned __int8, __int16, float, unsigned __int8))drawAutoAimCrosshair);

	// No rotate torso
	plugin::patch::PutRetn0(0x4EDDB0);

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
	};
	plugin::patch::RedirectCall(0x4F0464, (void(__fastcall*)(CPlayerPed*, int, CPad*))processWeaponSwitch);

	// No smooth weapon spray
	plugin::patch::Nop(0x4F13C8, 9);
}

bool ClassicAxis::IsAbleToAim(CPed* ped) {
	ePedState s = ped->m_ePedState;
	eMoveState m = ped->m_eMoveState;

	switch (s) {
	case PEDSTATE_NONE:
	case PEDSTATE_IDLE:
	case PEDSTATE_FLEE_POSITION:
	case PEDSTATE_FLEE_ENTITY:
	case PEDSTATE_ATTACK:
	case PEDSTATE_FIGHT:
	case PEDSTATE_AIMGUN:
		return m != PEDMOVE_SPRINT && ped->IsPedInControl();
	default:
		return false;
	}
}

bool ClassicAxis::IsWeaponPossiblyCompatible(CPed* ped) {
	const eWeaponType weaponType = ped->m_aWeapons[ped->m_nCurrentWeapon].m_eWeaponType;
	CWeaponInfo* info = CWeaponInfo::GetWeaponInfo(weaponType);

	switch (weaponType) {
	case WEAPONTYPE_FLAMETHROWER:
		info->m_bCanAim = true;
		break;
	}

	return (info->m_bCanAim || info->m_bCanAimWithArm) && !info->m_bThrow && !info->m_bHeavy && !info->m_b1stPerson;
}

bool ClassicAxis::IsTypeMelee(CPed* ped) {
	const eWeaponType weaponType = ped->m_aWeapons[ped->m_nCurrentWeapon].m_eWeaponType;

	switch (weaponType) {
	case WEAPONTYPE_UNARMED:
	case WEAPONTYPE_BASEBALLBAT:
	case WEAPONTYPE_MOLOTOV:
	case WEAPONTYPE_GRENADE:
	case WEAPONTYPE_DETONATOR:
		return true;
	}

	return false;
}
