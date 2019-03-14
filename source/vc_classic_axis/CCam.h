#pragma once

#define DEFAULT_FOV 70.0f

#include <math.h>
#include "eCameraMode.h"
#include "CVector.h"

class CCam {
public:
	bool bBelowMinDist;
	bool bBehindPlayerDesired;
	bool m_bCamLookingAtVector;
	bool m_bCollisionChecksOn;
	bool m_bFixingBeta;
	bool m_bTheHeightFixerVehicleIsATrain;
	bool LookBehindCamWasInFront;
	bool LookingBehind;
	bool LookingLeft;
	bool LookingRight;
	bool ResetStatics;
	bool Rotating;
	eCameraMode Mode;
	uint32_t m_uiFinishTime;
	int m_iDoCollisionChecksOnFrameNum;
	int m_iDoCollisionCheckEveryNumOfFrames;
	int m_iFrameNumWereAt;
	int m_iRunningVectorArrayPos;
	int m_iRunningVectorCounter;
	int DirectionWasLooking;
	float f_max_role_angle;
	float fRoll;
	float fRollSpeed;
	float m_fSyphonModeTargetZOffSet;
	float m_fAmountFractionObscured;
	float m_fAlphaSpeedOverOneFrame;
	float m_fBetaSpeedOverOneFrame;
	float m_fBufferedTargetBeta;
	float m_fBufferedTargetOrientation;
	float m_fBufferedTargetOrientationSpeed;
	float m_fCamBufferedHeight;
	float m_fCamBufferedHeightSpeed;
	float m_fCloseInPedHeightOffset;
	float m_fCloseInPedHeightOffsetSpeed;
	float m_fCloseInCarHeightOffset;
	float m_fCloseInCarHeightOffsetSpeed;
	float m_fDimensionOfHighestNearCar;
	float m_fDistanceBeforeChanges;
	float m_fFovSpeedOverOneFrame;
	float m_fMinDistAwayFromCamWhenInterPolating;
	float m_fPedBetweenCameraHeightOffset;
	float m_fPlayerInFrontSyphonAngleOffSet;
	float m_fRadiusForDead;
	float m_fRealGroundDist;
	float m_fTargetBeta;
	float m_fTimeElapsedFloat;
	float m_fTilt;
	float m_fTiltSpeed;
	float m_fTransitionBeta;
	float m_fTrueBeta;
	float m_fTrueAlpha;
	float m_fInitialPlayerOrientation;
	float Alpha;
	float AlphaSpeed;
	float FOV;
	float FOVSpeed;
	float Beta;
	float BetaSpeed;
	float fDistance;
	float fDistanceSpeed;
	float CA_MIN_DISTANCE;
	float CA_MAX_DISTANCE;
	float fSpeedVar;
	float m_fTargetZoomGroundOne;
	float m_fTargetZoomGroundTwo;
	float m_fTargetZoomGroundThree;
	float m_fTargetZoomOneZExtra;
	float m_fTargetZoomTwoZExtra;
	float m_fTargetZoomThreeZExtra;
	float m_fTargetZoomZCloseIn;
	float m_fMinRealGroundDist;
	float m_fTargetCloseInDist;
	CVector m_cvecSourceSpeedOverOneFrame;
	CVector m_cvecTargetSpeedOverOneFrame;
	CVector m_cvecUpOverOneFrame;
	CVector m_cvecTargetCoorsForFudgeInter;
	CVector m_cvecCamFixedModeVector;
	CVector m_cvecCamFixedModeSource;
	CVector m_cvecCamFixedModeUpOffSet;
	CVector m_vecLastAboveWaterCamPosition;
	CVector m_vecBufferedPlayerBodyOffset;
	CVector Front;
	CVector Source;
	CVector SourceBeforeLookBehind;
	CVector Up;
	CVector m_arrPreviousVectors[2];
	CEntity *CamTargetEntity;
	float m_fCameraDistance;
	float m_fIdealAlpha;
	float m_fPlayerVelocity;
	CAutomobile *m_pLastCarEntered;
	CPed *m_pLastPedLookedAt;
	bool m_bFirstPersonRunAboutActive;

public:
	static int m_dwTimeToRestoreMove;

public:
	static void __fastcall ProcessFollowPed(int, int, CVector const& target, float, float, float);
	static void __fastcall ProcessAimWeapon(int, int, CVector const & target, float targetOrient, float a4, float a5);
	static void __fastcall ProcessFollowVeh(int, int, CVector const & target, float a3, float a4, float a5);
	static bool __fastcall ProcessPlayerMovements(int a1, int);
	static bool __fastcall ProcessShootingDirection(int a1, int);
	static void ReturnVoid();

public:
	void ProcessFollowPedStandard(CVector const& target, float targetOrient);
	void ProcessAimWeaponStandard(CVector const & target, float targetOrient);
	void ProcessFollowVehicleStandard(CVector const & atarget, float targetOrient);
	void GetVectorsReadyForRW();

public:
	void Process();
	void ProcessSpecialHeightRoutines();
	void ProcessFollowPedClassic(CVector const & target, float targetOrient, int a4, int a5);
	void ProcessCamOnAString(CVector const & target, float targetOrient, int a4, int a5);
	void CamOnAStringUnobscured(CVector const & target, float distval);
	void WorkOutCamHeight(CVector const & target, float targetOrientation, float targetHeight);
	char RotCamIfInFrontCar(CVector const & target, float targetOrientation);
	__int16 FixCamWhenObscuredByVehicle(CVector const & target);
};
