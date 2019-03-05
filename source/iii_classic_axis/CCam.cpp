#include "CGTA3D.h"
#include "CCam.h"
#include "CWorld.h"
#include "CCamera.h"
#include "CScene.h"
#include "CTimer.h"
#include "CGeneral.h"
#include "CBaseModelInfo.h"
#include "CModelInfo.h"
#include "CWeaponEffects.h"
#include "eModelIndices.h"
#include "Settings.h"
#include "CWeaponInfo.h"

static CPatch InjectPatches([]() {
	if (GetSetting.bProcess_FollowPed) {
		CPatch::RedirectCall(0x459A7C, CCam::ProcessFollowPed);
		CPatch::Nop(0x459A65, 2);

		// fps to 3rd - m16.
		CPatch::Set<BYTE>(0x4F1F74, -1);

		// No fight cam.
		CPatch::Nop(0x469226, 7);
		CPatch::Nop(0x469260, 7);

		// Player movements.
		int m_dwAddress0[] = {	0x4F2685,
								0x469292,
								0x4C7673,
								0x4F03D5,
								0x4D76CE,
								0x45DB98
		};
		for (int i = 0; i < 6; i++)
			CPatch::RedirectCall(m_dwAddress0[i], CCam::ProcessPlayerMovements);

		// Shooting direction.
		int m_dwAddress1[] = {	0x4E6562,
								0x55D88B,
								0x560C25
		};
		for (int i = 0; i < 3; i++)
			CPatch::RedirectCall(m_dwAddress1[i], CCam::ProcessShootingDirection);

		CPatch::RedirectCall(0x468E46, CCam::ReturnVoid);
	}

	if (GetSetting.bProcess_FollowVeh) {
		CPatch::RedirectCall(0x459A54, CCam::ProcessFollowVeh);
		CPatch::RedirectCall(0x459B36, CCam::ProcessFollowVeh);

		// Veh/Foo 
		CPatch::Nop(0x4713DB, 2);
		CPatch::Nop(0x47143B, 2);
	}
});

void __fastcall CCam::ProcessFollowPed(int, int, CVector const& target, float targetOrient, float a4, float a5) {
	switch (CPed::m_bDoAiming) {
	case 0:
		TheCamera.Cams->ProcessFollowPedStandard(target, targetOrient);
		break;
	case 1:
		TheCamera.Cams->ProcessAimWeaponStandard(target, targetOrient);
		break;
	}
}

void __fastcall CCam::ProcessFollowVeh(int, int, CVector const& target, float targetOrient, float a4, float a5) {
	TheCamera.Cams->ProcessFollowVehicleStandard(target, targetOrient);
}

bool __fastcall CCam::ProcessPlayerMovements(int a1, int) {
	if (Pads->m_bDisablePlayerControls)
		return false;

	if (CCamera::m_bWalkSideways)
		return true;
	else
		return false;
}

bool __fastcall CCam::ProcessShootingDirection(int a1, int) {
	if (Pads->m_bDisablePlayerControls)
		return false;;

	if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget)
		return false;

	if (TheCamera.Cams->Mode == MODE_FOLLOWPED && TheCamera.Cams->Mode != MODE_FIXED && CPed::m_bDoAiming && !FindPlayerPed()->BeQuiteAndEasy())
		return true;
	else
		return false;
}

void CCam::ReturnVoid() {

}

/////////////////////////////

void CCam::ProcessFollowPedStandard(CVector const& target, float targetOrient) {	
	m_bFixingBeta = 0;
	bBelowMinDist = 0;
	bBehindPlayerDesired = 0;

	RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);

	CVector IVOffset = CVector(0.32f, 0.0f, 0.0f);
	CVector TargetCoors;

	if (GetSetting.bIVOnFootCamera) 
		TargetCoors = FindPlayerPed()->TransformFromObjectSpace(IVOffset);
	else
		TargetCoors = target;

	TargetCoors.z = TargetCoors.z + 0.05f + m_fSyphonModeTargetZOffSet;

	CVector Dist = Source - TargetCoors;
	float Length = Dist.Magnitude();
	float LengthTemp = 0.0f;

	if (GetSetting.bDynamicFOV) { // IV Dynamic FOV.
		TargetCoors = TargetCoors;
		FOV = GetSetting.fFOV + sin(-Alpha) * 50.0f;

		if (TheCamera.PedZoomIndicator == 2.0f)
			LengthTemp += sin(-Alpha) * 45.0f;
		LengthTemp -= FindPlayerPed()->GetPosition().z - 1.0f;

		if (LengthTemp <= 0.0f)
			LengthTemp = 0.0f;
		if (LengthTemp >= 15.0f)
			LengthTemp = 15.0f;

		Length = Length + LengthTemp;

		if (FOV <= GetSetting.fFOV) {
			FOV = GetSetting.fFOV;
		}
		if (FOV >= 100) {
			FOV = 100;
		}
	}
	else
		FOV = GetSetting.fFOV;
	//

	if (ResetStatics) {
		Rotating = 0;
		m_bCollisionChecksOn = true;
	}

	float IdealLength = 0.0f;
	if (TheCamera.PedZoomIndicator == 1.0) IdealLength = 2.090556f;
	if (TheCamera.PedZoomIndicator == 2.0) IdealLength = 3.34973f;
	if (TheCamera.PedZoomIndicator == 3.0) IdealLength = 4.704914f;
	if (TheCamera.PedZoomIndicator == 4.0) IdealLength = 2.090556f;

	if (Length != 0.0f) {
		Dist.x *= IdealLength / Length;
		Dist.y *= IdealLength / Length;
		Dist.z *= IdealLength / Length;
	}
	else {
		Dist.x = 1.0f;
		Dist.y = 1.0f;
		Dist.z = 0.0f;
	}

	Length = 0.25f + (Dist.Magnitude() / 2) + TheCamera.m_fPedZoomValueSmooth;

	if (!GetSetting.bNoAutoFoc)
	if ((pXboxPad->HasPadInHands() && FindPlayerPed()->m_fTotSpeed >= 0.06f) && !LookingBehind) {
		Beta = CGeneral::GetATanOfXY(Dist.x, Dist.y);
		Alpha = CGeneral::GetATanOfXY(Dist.Magnitude() + DEGTORAD(10.0f), Dist.z - DEGTORAD(2.0f));
	}
	
	while (Beta >= PI) Beta -= 2.0f * PI;
	while (Beta < -PI) Beta += 2.0f * PI;
	while (Alpha >= PI) Alpha -= 2.0f * PI;
	while (Alpha < -PI) Alpha += 2.0f * PI;

	// Movements
	if (!Pads->m_bDisablePlayerControls) {
		if (!TheCamera.m_bCamDirectlyBehind && !TheCamera.m_bCamDirectlyInFront && !LookingBehind && !LookingLeft && !LookingRight) {
			if (CPad::NewMouseControllerState.X != 0.0 || CPad::NewMouseControllerState.Y != 0.0) {
				float fFV = FOV * 0.0125;

				//Front.y = CPad::NewMouseControllerState.Y;
				//Front.x = CPad::NewMouseControllerState.X;
				BetaSpeed = 0.0f;
				AlphaSpeed = 0.0f;
				Alpha -= CPad::NewMouseControllerState.Y * 4.0 * fFV * TheCamera.m_fMouseAccelVertical;
				Beta += CPad::NewMouseControllerState.X * -2.5 * fFV * TheCamera.m_fMouseAccelHorzntl;
			}

			if (pXboxPad->HasPadInHands()) {
				Alpha -= (Pads->LookAroundUpDown() *  GetSetting.fRightStickVerticalSensitivity) / 1280.0f;
				Beta -= (Pads->LookAroundLeftRight() * GetSetting.fRightStickHorizontalSensitivity) / 1280.0f;
			}
		}
	}

	if (Alpha > DEGTORAD(80.0f)) Alpha = DEGTORAD(80.0f);
	if (Alpha < -DEGTORAD(50.0f)) Alpha = -DEGTORAD(50.0f);

	Dist = CVector(cos(Beta) * cos(Alpha), sin(Beta) * cos(Alpha), sin(Alpha));
	Dist = Front + Dist * Length;

	Source = TargetCoors + Dist - Front;
	SourceBeforeLookBehind = TargetCoors + Dist;
	m_cvecTargetCoorsForFudgeInter = TargetCoors;
	m_fDistanceBeforeChanges = (Source - TargetCoors).Magnitude();

	CColPoint colpoint;
	CEntity *e = NULL;

	if (CWorld::ProcessLineOfSight(TargetCoors, Source, colpoint, e, true, true, false, true, false, true, true)) {
		Source = colpoint.m_vPoint;

		CVector d = Source - TargetCoors;
		float l = d.Magnitude();
		if (l > 0.4f)
			d = d / l * (l - 0.3f);
		Source = TargetCoors + d;

		if ((TargetCoors - Source).Magnitude2d() < 2.0f)
			RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);
	}

	CWorld::pIgnoreEntity = CamTargetEntity;
	if (CWorld::ProcessLineOfSight(TargetCoors, Source, colpoint, e, true, true, true, true, false, true, true)) {
		Source = colpoint.m_vPoint;

		CVector d = Source - TargetCoors;
		float l = d.Magnitude();
		if (l > 0.3f)
			d = d / l * (l - 0.3f);
		Source = TargetCoors + d;

		if ((TargetCoors - Source).Magnitude2d() < 2.0f)
			RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);
	}
	CWorld::pIgnoreEntity = NULL;

	if (TheCamera.m_bUseTransitionBeta)
		Beta = m_fTransitionBeta;
	//Beta = CGeneral::GetATanOfXY(1.85 * sin(m_fTransitionBeta) + TargetCoors.x - TargetCoors.x, Source.y - TargetCoors.y);

	if (TheCamera.m_bCamDirectlyBehind) {
		m_bCollisionChecksOn = 1;
		Beta = targetOrient + PI;
		Alpha = DEGTORAD(2.0);
	}
	if (TheCamera.m_bCamDirectlyInFront) {
		Beta = targetOrient;
		Alpha = DEGTORAD(2.0);
	}

	Front = TargetCoors - Source;

	m_fRealGroundDist = sqrt(Front.y * Front.y + Front.x * Front.x);
	m_fMinDistAwayFromCamWhenInterPolating = m_fRealGroundDist;
	Front.Normalise();

	GetVectorsReadyForRW();

	TheCamera.m_bCamDirectlyBehind = false;
	TheCamera.m_bCamDirectlyInFront = false;
	ResetStatics = false;
}

void CCam::ProcessAimWeaponStandard(CVector const& target, float targetOrient) {
	m_bFixingBeta = 0;
	bBelowMinDist = 0;
	bBehindPlayerDesired = 0;

	RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);

	CVector aimoffset = CVector(0.5f, 1.0f, 0.1f);

	if (TheCamera.PedZoomIndicator == 1.0)
		aimoffset = CVector(0.425f, 0.935f, 0.105f);

	CVector TargetCoors = FindPlayerPed()->TransformFromObjectSpace(aimoffset);
	CColPoint colpoint;
	CEntity *e = NULL;

	CPed::m_bHideCrosshair = false;
	if (CWorld::ProcessLineOfSight(TargetCoors, Source, colpoint, e, true, false, false, true, false, true, true)) {
		TargetCoors = target;
		CPed::m_bHideCrosshair = true;
	}

	TargetCoors.z = TargetCoors.z + 0.05f + m_fSyphonModeTargetZOffSet - (sin(Alpha));

	CVector Dist = TargetCoors - Source;
	float Length = Dist.Magnitude();
	float LengthTemp = 0.0f;

	LengthTemp += sin(Alpha) * 10.0f;

	if (LengthTemp <= 0.0f)
		LengthTemp = 0.0f;
	if (LengthTemp >= 10.0f)
		LengthTemp = 10.0f;

	if (TheCamera.PedZoomIndicator == 2.0f)
		Length = Length + LengthTemp;

	FOV = GetSetting.fFOV;
	if (ResetStatics) {
		Rotating = 0;
		m_bCollisionChecksOn = true;
	}

	float IdealLength = 0.0f;
	if (TheCamera.PedZoomIndicator == 1.0) IdealLength = 2.090556f;
	if (TheCamera.PedZoomIndicator == 2.0) IdealLength = 3.34973f;
	if (TheCamera.PedZoomIndicator == 3.0) IdealLength = 4.704914f;
	if (TheCamera.PedZoomIndicator == 4.0) IdealLength = 2.090556f;

	if (Length != 0.0f) {
		Dist.x *= IdealLength / Length;
		Dist.y *= IdealLength / Length;
		Dist.z *= IdealLength / Length;
	}
	else {
		Dist.x = 1.0f;
		Dist.y = 1.0f;
		Dist.z = 0.0f;
	}

	Length = 0.25f + (Dist.Magnitude() / 2) + TheCamera.m_fPedZoomValueSmooth;

	if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget && !LookingBehind) {
		if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pPointGunAt)
			Beta = CGeneral::GetATanOfXY(Source.x - CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pPointGunAt->m_matrix.pos.x, Source.y - CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_pPointGunAt->m_matrix.pos.y);
		Alpha = CGeneral::GetATanOfXY(Dist.Magnitude2d(), Dist.z);
	}

	while (Beta >= PI) Beta -= 2.0f * PI;
	while (Beta < -PI) Beta += 2.0f * PI;
	while (Alpha >= PI) Alpha -= 2.0f * PI;
	while (Alpha < -PI) Alpha += 2.0f * PI;

	// Movements
	if (!Pads->m_bDisablePlayerControls) {
		if (!TheCamera.m_bCamDirectlyBehind && !TheCamera.m_bCamDirectlyInFront && !LookingBehind && !LookingLeft && !LookingRight) {
			if (CPad::NewMouseControllerState.X != 0.0 || CPad::NewMouseControllerState.Y != 0.0) {
				float fFV = FOV * 0.0125;

				//Front.y = CPad::NewMouseControllerState.Y;
				//Front.x = CPad::NewMouseControllerState.X;
				BetaSpeed = 0.0f;
				AlphaSpeed = 0.0f;
				Alpha -= CPad::NewMouseControllerState.Y * 4.0 * fFV * TheCamera.m_fMouseAccelVertical;
				Beta += CPad::NewMouseControllerState.X * -2.5 * fFV * TheCamera.m_fMouseAccelHorzntl;
			}

			if (pXboxPad->HasPadInHands()) {
				Alpha -= (Pads->LookAroundUpDown() *  GetSetting.fRightStickVerticalSensitivity) / 1280.0f;
				Beta -= (Pads->LookAroundLeftRight() * GetSetting.fRightStickHorizontalSensitivity) / 1280.0f;
			}
		}
	}

	if (Alpha > DEGTORAD(90.0f)) Alpha = DEGTORAD(90.0f);
	if (Alpha < -DEGTORAD(100.0f)) Alpha = -DEGTORAD(100.0f);

	Dist = CVector(cos(Beta), sin(Beta), sin(Alpha));
	Dist = Front + Dist * Length;

	Source = TargetCoors + Dist - Front;
	SourceBeforeLookBehind = TargetCoors + Dist;
	m_cvecTargetCoorsForFudgeInter = TargetCoors;
	m_fDistanceBeforeChanges = (Source - TargetCoors).Magnitude();

	if (CWorld::ProcessLineOfSight(TargetCoors, Source, colpoint, e, true, true, false, true, false, true, true)) {
		Source = colpoint.m_vPoint;

		CVector d = Source - TargetCoors;
		float l = d.Magnitude();
		if (l > 0.3f)
			d = d / l * (l - 0.3f);
		Source = TargetCoors + d;

		if ((TargetCoors - Source).Magnitude2d() < 2.0f)
			RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);
	}

	CWorld::pIgnoreEntity = CamTargetEntity;

	FixCamWhenObscuredByVehicle(TargetCoors);

	if (CWorld::ProcessLineOfSight(TargetCoors, Source, colpoint, e, true, true, false, true, false, true, true)) {
		Source = colpoint.m_vPoint;

		CVector d = Source - TargetCoors;
		float l = d.Magnitude();
		if (l > 0.3f)
			d = d / l * (l - 0.3f);
		Source = TargetCoors + d;

		if ((TargetCoors - Source).Magnitude2d() < 2.0f)
			RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);
	}
	CWorld::pIgnoreEntity = NULL;

	if (TheCamera.m_bCamDirectlyBehind) {
		m_bCollisionChecksOn = 1;
		Beta = targetOrient + PI;
		Alpha = DEGTORAD(2.0);
	}
	if (TheCamera.m_bCamDirectlyInFront) {
		Beta = targetOrient;
		Alpha = DEGTORAD(2.0);
	}

	Front = TargetCoors - Source;

	m_fRealGroundDist = sqrt(Front.y * Front.y + Front.x * Front.x);
	m_fMinDistAwayFromCamWhenInterPolating = m_fRealGroundDist;
	Front.Normalise();

	GetVectorsReadyForRW();

	TheCamera.m_bCamDirectlyBehind = false;
	TheCamera.m_bCamDirectlyInFront = false;
	ResetStatics = false;

	if (!CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget)
		CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_fFPSMoveHeading = TheCamera.Find3rdPersonQuickAimPitch() * 0.75f;
}

void CCam::ProcessFollowVehicleStandard(CVector const& atarget, float targetOrient) {
	m_bFixingBeta = 0;
	bBelowMinDist = 0;
	bBehindPlayerDesired = 0;

	if ((CamTargetEntity->m_nType & 7) != 2)
		return;

	RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);

	CVector TargetCoors;

	if (GetSetting.bIVVehicleCamera && FindPlayerVehicle())
		TargetCoors = FindPlayerVehicle()->TransformFromObjectSpace(CVector(-0.32f, 0.0f, 0.0f));
	else
		TargetCoors = atarget;

	CVector VehSize = (CModelInfo::ms_modelInfoPtrs[CamTargetEntity->m_nModelIndex]->m_pColModel->m_boundBox.m_vecMax - CModelInfo::ms_modelInfoPtrs[CamTargetEntity->m_nModelIndex]->m_pColModel->m_boundBox.m_vecMin);
	
	if (CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle)
		VehSize += CVector(0.5, 5.0f, 0.5f);

	float distval = VehSize.Magnitude();

	TargetCoors.z = TargetCoors.z - 0.85f + VehSize.z;

	CVector Dist;
	Dist.x = TargetCoors.x - Source.x;
	Dist.y = TargetCoors.y - Source.y;
	Dist.z = Source.z - TargetCoors.z;
	float Length = Dist.Magnitude();
	float LengthTemp = 0.0f;

	if (GetSetting.bDynamicFOV) { // IV Dynamic FOV.
		FOV = GetSetting.fFOV + sin(-Alpha) * 50.0f;
		if (TheCamera.CarZoomIndicator == 2.0f)
			LengthTemp += sin(-Alpha) * 45.0f;

		if (FindPlayerVehicle())
			LengthTemp -= FindPlayerVehicle()->GetPosition().z - 1.0f;

		if (LengthTemp <= 0.0f)
			LengthTemp = 0.0f;
		if (LengthTemp >= 15.0f)
			LengthTemp = 15.0f;

		Length = Length + LengthTemp;

		if (FOV <= GetSetting.fFOV)
			FOV = GetSetting.fFOV;
		if (FOV >= 100) {
			FOV = 100;
		}
	}
	else
		FOV = GetSetting.fFOV;
	//

	if (ResetStatics) {
		AlphaSpeed = 0.0f;
		if (TheCamera.m_bIdleOn)
			TheCamera.m_uiTimeWeEnteredIdle = CTimer::m_snTimeInMilliseconds;
	}

	CA_MAX_DISTANCE = distval - 0.1f + TheCamera.CarZoomValueSmooth;
	CA_MIN_DISTANCE = min(distval * 0.6f, 3.5f);

	if (CA_MIN_DISTANCE >= 0.60000002 * distval)
		CA_MIN_DISTANCE = 0.60000002 * distval;

	Length = CA_MAX_DISTANCE + 0.5f;

	float speed = 0.10f;
	if (CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle)
		speed = 0.10f;

	if (!GetSetting.bNoAutoFoc)
		if ((pXboxPad->HasPadInHands() && FindPlayerVehicle() && FindPlayerVehicle()->m_fTotSpeed > speed) || (((CTimer::m_snTimeInMilliseconds > m_dwTimeToRestoreMove)) && FindPlayerVehicle() && FindPlayerVehicle()->m_fTotSpeed > speed && !TheCamera.m_bCamDirectlyBehind && !TheCamera.m_bCamDirectlyInFront) && !LookingBehind) {
			Beta = CGeneral::GetATanOfXY(Dist.x, Dist.y);
			Alpha = CGeneral::GetATanOfXY(Dist.Magnitude2d() + DEGTORAD(60.0f), Dist.z + DEGTORAD(6.0f));
		}

	while (Alpha > PI) Alpha -= 2 * PI;
	while (Alpha < -PI) Alpha += 2 * PI;
	while (Beta > PI) Beta -= 2 * PI;
	while (Beta < -PI) Beta += 2 * PI;

	// Movements
	static bool m_bMotion;
	if (FindPlayerVehicle() &&
		(FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[0] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[1] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[2] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[3] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[4] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[5] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[6] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[7] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[8] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[9] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[10] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[11] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[12] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[13] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[14] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[15] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[16] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[17] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[18] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[19] ||
			FindPlayerVehicle()->m_nModelIndex == GetSetting.ModelID[20])) {
		m_bMotion = false;
	}
	else
		m_bMotion = true;

	if (!Pads->m_bDisablePlayerControls) {
		if (!TheCamera.m_bCamDirectlyBehind && !TheCamera.m_bCamDirectlyInFront && !LookingBehind && !LookingLeft && !LookingRight) {
			if (CPad::NewMouseControllerState.X != 0.0 || CPad::NewMouseControllerState.Y != 0.0) {
				float fFV = FOV * 0.0125;

				//Front.y = CPad::NewMouseControllerState.Y;
				//Front.x = CPad::NewMouseControllerState.X;
				BetaSpeed = 0.0f;
				AlphaSpeed = 0.0f;
				Alpha -= CPad::NewMouseControllerState.Y * 4.0 * fFV * TheCamera.m_fMouseAccelVertical;
				Beta += CPad::NewMouseControllerState.X * -2.5 * fFV * TheCamera.m_fMouseAccelHorzntl;
			}

			if (pXboxPad->HasPadInHands() && m_bMotion) {
				Alpha -= (Pads->LookAroundUpDown() *  GetSetting.fRightStickVerticalSensitivity) / 1280.0f;
				Beta -= (Pads->LookAroundLeftRight() * GetSetting.fRightStickHorizontalSensitivity) / 1280.0f;
			}
		}
	}

	if (Alpha > DEGTORAD(80.0f)) Alpha = DEGTORAD(80.0f);
	if (Alpha < -DEGTORAD(20.0f)) Alpha = -DEGTORAD(20.0f);

	Dist = CVector(cos(Beta) * cos(Alpha), sin(Beta) * cos(Alpha), sin(Alpha));
	Dist.x = Dist.x * Length + Front.x;
	Dist.y = Dist.y * Length + Front.y;
	Dist.z = Front.z + Dist.z * Length;

	Source.x = Front.x - Dist.x + TargetCoors.x;
	Source.y = Front.y - Dist.y + TargetCoors.y;
	Source.z = TargetCoors.z + Dist.z - Front.z;
	SourceBeforeLookBehind = Front - Dist + TargetCoors;
	m_cvecTargetCoorsForFudgeInter = TargetCoors;
	m_fDistanceBeforeChanges = (Source - TargetCoors).Magnitude();

	CColPoint colpoint;
	CEntity *e = NULL;

	CWorld::pIgnoreEntity = CamTargetEntity;

	FixCamWhenObscuredByVehicle(TargetCoors);

	if (CWorld::ProcessLineOfSight(TargetCoors, Source, colpoint, e, true, false, false, true, true, true, true)) {
		Source = colpoint.m_vPoint;

		CVector d = Source - TargetCoors;
		float l = d.Magnitude();

		if (l > 0.4f) {
			d = d / l * (l - 0.25f);
		}

		Source = TargetCoors + d;
	}
	CWorld::pIgnoreEntity = NULL;

	if (DirectionWasLooking != 3) {
		TheCamera.m_bCamDirectlyBehind = true;
	}

	if (TheCamera.m_bUseTransitionBeta)
		Beta = m_fTransitionBeta;

	if (TheCamera.m_bCamDirectlyBehind) {
		m_bCollisionChecksOn = 1;
		Beta = targetOrient;
		Alpha = DEGTORAD(5.0);
	}
	if (TheCamera.m_bCamDirectlyInFront) {
		Beta = targetOrient + PI;
		Alpha = DEGTORAD(5.0);
	}

	Front = TargetCoors - Source;

	m_fRealGroundDist = Front.Magnitude();
	m_fMinDistAwayFromCamWhenInterPolating = m_fRealGroundDist;
	Front.Normalise();

	GetVectorsReadyForRW();

	TheCamera.m_bCamDirectlyBehind = false;
	TheCamera.m_bCamDirectlyInFront = false;
	ResetStatics = false;

	// Extra stuff.
	if (FindPlayerVehicle() && !LookingBehind && !LookingLeft && !LookingRight && GetSetting.bControlVehParts) {
		CAutomobile* arg = (CAutomobile*)FindPlayerVehicle();

		if (FindPlayerVehicle()->m_nModelIndex == MI_FIRETRUK) {
			arg->m_fDoomVerticalRotation = (FindPlayerHeading() - (0) + atan2(Dist.x, Dist.y));
			arg->m_fDoomHorizontalRotation = sin(Alpha);

			if (arg->m_aCarNodes[CAR_BUMP_REAR]) {
				CMatrix mat;
				CVector matpos;

				mat.m_bOwnsAttachedMatrix = 0;
				mat.m_pAttachMatrix = 0;
				mat.Attach(&arg->m_aCarNodes[CAR_BUMP_REAR]->modelling, 0);
				matpos = mat.pos;
				mat.SetRotateZ(-arg->m_fDoomVerticalRotation);
				mat.pos += matpos;
				mat.UpdateRW();

				mat.~CMatrix();
			}

		}
		if (FindPlayerVehicle()->m_nModelIndex == MI_RHINO) {
			arg->m_fDoomVerticalRotation = -(FindPlayerHeading() - (0) + atan2(Dist.x, Dist.y));
			arg->m_fDoomHorizontalRotation = sin(Alpha);
		}

	}
}

void CCam::GetVectorsReadyForRW() {
	CVector right;
	Up = CVector(0.0f, 0.0f, 1.0f);
	Front.Normalise();
	if (Front.x == 0.0f && Front.y == 0.0f) {
		Front.x = 0.0001f;
		Front.y = 0.0001f;
	}
	right = CrossProduct(Front, Up);
	right.Normalise();
	Up = CrossProduct(right, Front);
}

void CCam::Process() {
	((void(__thiscall *)(CCam *))0x4596A0)(this);
}

void CCam::ProcessSpecialHeightRoutines() {
	((void(__thiscall *)(CCam *))0x467400)(this);
}

void CCam::CamOnAStringUnobscured(CVector const& target, float distval) {
	((void(__thiscall *)(CCam *, CVector const&, float))0x457210)(this, target, distval);
}

void CCam::WorkOutCamHeight(CVector const& target, float targetOrientation, float targetHeight) {
	((void(__thiscall *)(CCam *, CVector const&, float, float))0x466650)(this, target, targetOrientation, targetHeight);
}

char CCam::RotCamIfInFrontCar(CVector const& target, float targetOrientation) {
	return ((char(__thiscall *)(CCam *, CVector const&, float))0x465DA0)(this, target, targetOrientation);
}

char CCam::FixCamIfObscured(CVector const& targetCoors, float z, float targetOrientation) {
	return ((char(__thiscall *)(CCam *, CVector const&, float, float))0x457B90)(this, targetCoors, z, targetOrientation);
}

__int16 CCam::FixCamWhenObscuredByVehicle(CVector const& target) {
	return ((__int16(__thiscall *)(CCam *, CVector const&))0x457A80)(this, target);
}

void CCam::ProcessFollowPedClassic(CVector const& target, float a3, int a4, int a5) {
	((void(__thiscall *)(CCam *, CVector const&, float, int, int))0x45E3A0)(this, target, a3, a4, a5);
}

void CCam::ProcessCamOnAString(CVector const& target, float a3, int a4, int a5) {
	((void(__thiscall *)(CCam *, CVector const&, float, int, int))0x45C090)(this, target, a3, a4, a5);
}
