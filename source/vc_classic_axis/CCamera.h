#pragma once

#include "CPlaceable.h"
#include "CEntity.h"
#include "CPed.h"
#include "CAutomobile.h"
#include "eCameraMode.h"
#include "CCam.h"

struct CCamPathSplines {
	float m_arr_PathData[800];
};

struct CTrainCamNode {
	CVector m_cvecCamPosition;
	CVector m_cvecPointToLookAt;
	CVector m_cvecMinPointInRange;
	CVector m_cvecMaxPointInRange;
	float m_fDesiredFOV;
	float m_fNearClip;
};

struct CQueuedMode {
	__int16 Mode;
	float Duration;
	__int16 MinZoom;
	__int16 MaxZoom;
};

struct CGarage;

class CCamera : CPlaceable {
public:
	bool m_bAboveGroundTrainNodesLoaded;
	bool m_bBelowGroundTrainNodesLoaded;
	bool m_bCamDirectlyBehind;
	bool m_bCamDirectlyInFront;
	bool m_bCameraJustRestored;
	bool m_bcutsceneFinished;
	bool m_bCullZoneChecksOn;
	bool m_bFirstPersonBeingUsed;
	bool m_bJustJumpedOutOf1stPersonBecauseOfTarget;
	bool m_bIdleOn;
	bool m_bInATunnelAndABigVehicle;
	bool m_bInitialNodeFound;
	bool m_bInitialNoNodeStaticsSet;
	bool m_bIgnoreFadingStuffForMusic;
	bool m_bPlayerIsInGarage;
	bool m_bPlayerWasOnBike;
	bool m_bJustCameOutOfGarage;
	bool m_bJustInitalised;
	uint8_t m_bJust_Switched;
	bool m_bLookingAtPlayer;
	bool m_bLookingAtVector;
	bool m_bMoveCamToAvoidGeom;
	bool m_bObbeCinematicPedCamOn;
	bool m_bObbeCinematicCarCamOn;
	bool m_bRestoreByJumpCut;
	bool m_bUseNearClipScript;
	bool m_bStartInterScript;
	uint8_t m_bStartingSpline;
	bool m_bTargetJustBeenOnTrain;
	bool m_bTargetJustCameOffTrain;
	bool m_bUseSpecialFovTrain;
	bool m_bUseTransitionBeta;
	bool m_bUseScriptZoomValuePed;
	bool m_bUseScriptZoomValueCar;
	bool m_bWaitForInterpolToFinish;
	bool m_bItsOkToLookJustAtThePlayer;
	bool m_bWantsToSwitchWidescreenOff;
	bool m_WideScreenOn;
	bool m_1rstPersonRunCloseToAWall;
	bool m_bHeadBob;
	bool m_bVehicleSuspenHigh;
	bool m_bEnable1rstPersonCamCntrlsScript;		 
	bool m_bAllow1rstPersonWeaponsCamera;
	bool m_bFailedCullZoneTestPreviously;
	bool m_FadeTargetIsSplashScreen;
	bool WorldViewerBeingUsed;                                  
	uint8_t ActiveCam; 
	uint32_t m_uiCamShakeStart; 
	uint32_t m_uiFirstPersonCamLastInputTime;
	uint32_t m_uiLongestTimeInMill;
	uint32_t m_uiNumberOfTrainCamNodes;
	uint8_t m_uiTransitionJUSTStarted;
	uint8_t m_uiTransitionState;
	uint32_t m_uiTimeLastChange;
	uint32_t m_uiTimeWeLeftIdle_StillNoInput;
	uint32_t m_uiTimeWeEnteredIdle;
	uint32_t m_uiTimeTransitionStart;
	uint32_t m_uiTransitionDuration;
	uint32_t m_uiTransitionDurationTargetCoors;
	int m_BlurBlue;
	int m_BlurGreen;
	int m_BlurRed;
	int m_BlurType;
	int m_iWorkOutSpeedThisNumFrames; 
	int m_iNumFramesSoFar;
	int m_iCurrentTrainCamNode;
	int m_motionBlur;
	int m_imotionBlurAddAlpha;
	int m_iCheckCullZoneThisNumFrames;
	int m_iZoneCullFrameNumWereAt;
	int WhoIsInControlOfTheCamera;
	float CamFrontXNorm, CamFrontYNorm;
	float CarZoomIndicator;
	float CarZoomValue;
	float CarZoomValueSmooth;
	float DistanceToWater;
	float FOVDuringInter;
	float LODDistMultiplier;
	float GenerationDistMultiplier;
	float m_fAlphaSpeedAtStartInter;
	float m_fAlphaWhenInterPol;
	float m_fAlphaDuringInterPol;
	float m_fBetaDuringInterPol;
	float m_fBetaSpeedAtStartInter;
	float m_fBetaWhenInterPol;
	float m_fFOVWhenInterPol;
	float m_fFOVSpeedAtStartInter;
	float m_fStartingBetaForInterPol;
	float m_fStartingAlphaForInterPol;
	float m_PedOrientForBehindOrInFront;	  
	float m_CameraAverageSpeed;
	float m_CameraSpeedSoFar;
	float m_fCamShakeForce;   
	float m_fCarZoomValueScript;
	float m_fFovForTrain;
	float m_fFOV_Wide_Screen;
	float m_fNearClipScript;
	float m_fOldBetaDiff; 
	float m_fPedZoomValue;
	float m_fPedZoomValueSmooth;
	float m_fPedZoomValueScript;
	float m_fPositionAlongSpline;
	float m_ScreenReductionPercentage;
	float m_ScreenReductionSpeed;
	float m_AlphaForPlayerAnim1rstPerson;
	float Orientation;
	float PedZoomIndicator;
	float PlayerExhaustion;
	float SoundDistUp;
	float SoundDistUpAsRead;
	float SoundDistUpAsReadOld;
	float m_fAvoidTheGeometryProbsTimer;
	int16_t m_nAvoidTheGeometryProbsDirn;
	float m_fWideScreenReductionAmount;
	float m_fStartingFOVForInterPol;
	static float &m_fMouseAccelVertical;
	static float &m_fMouseAccelHorzntl;
	static float &m_f3rdPersonCHairMultX;
	static float &m_f3rdPersonCHairMultY;
	CCam Cams[3];
	CGarage *pToGarageWeAreIn;
	CGarage *pToGarageWeAreInForHackAvoidFirstPerson;
	CQueuedMode m_PlayerMode;
	CQueuedMode PlayerWeaponMode;
	CVector m_PreviousCameraPosition;
	CVector m_RealPreviousCameraPosition; 
	CVector m_cvecAimingTargetCoors;
	CVector m_vecFixedModeVector;
	CVector m_vecFixedModeSource;
	CVector m_vecFixedModeUpOffSet;
	CVector m_vecCutSceneOffset;
	CVector m_cvecStartingSourceForInterPol;
	CVector m_cvecStartingTargetForInterPol;
	CVector m_cvecStartingUpForInterPol;
	CVector m_cvecSourceSpeedAtStartInter;
	CVector m_cvecTargetSpeedAtStartInter;
	CVector m_cvecUpSpeedAtStartInter;
	CVector m_vecSourceWhenInterPol;
	CVector m_vecTargetWhenInterPol;
	CVector m_vecUpWhenInterPol;
	CVector m_vecClearGeometryVec;
	CVector m_vecGameCamPos;
	CVector SourceDuringInter, TargetDuringInter, UpDuringInter;
	RwCamera* m_pRwCamera;
	CEntity *pTargetEntity;
	CCamPathSplines m_arrPathArray[2];
	CMatrix m_cameraMatrix;
	bool m_bGarageFixedCamPositionSet;
	bool m_vecDoingSpecialInterPolation;
	bool m_bScriptParametersSetForInterPol;
	bool m_bFading;
	bool m_bMusicFading;
	CMatrix m_viewMatrix;
	CVector m_vecFrustumNormals[4];
	CVector m_vecOldSourceForInter;
	CVector m_vecOldFrontForInter;
	CVector m_vecOldUpForInter;
	float m_vecOldFOVForInter;
	float m_fFLOATingFade;
	float m_fFLOATingFadeMusic;
	float m_fTimeToFadeOut;
	float m_fTimeToFadeMusic;
	float m_fFractionInterToStopMoving;
	float m_fFractionInterToStopCatchUp;
	float m_fFractionInterToStopMovingTarget;
	float m_fFractionInterToStopCatchUpTarget;
	float m_fGaitSwayBuffer;
	float m_fScriptPercentageInterToStopMoving;
	float m_fScriptPercentageInterToCatchUp;
	uint32_t m_fScriptTimeForInterPolation;
	int16_t m_iFadingDirection;
	int m_iModeObbeCamIsInForCar;
	int16_t m_iModeToGoTo;
	int16_t m_iMusicFadingDirection;
	int16_t m_iTypeOfSwitch;
	uint32_t m_uiFadeTimeStarted;
	uint32_t m_uiFadeTimeStartedMusic;

public:
	static char &m_nFadeColorsSet;
	static char &m_bUseMouse3rdPerson;
	bool m_bFixBetaDirection;

public:
	static void CamControlHook();
	int CamControl();
	void ClearPlayerWeaponMode();
	float Find3rdPersonQuickAimPitch();
	int GetLookDirection();
	char GetFading();
	int GetScreenFadeStatus();
	void SetFadeColour(char a2, char a3, int a4);
	int Fade(float a2, int a3);
	int ProcessFade();
	char ProcessMusicFade();
	static void __fastcall Process(CCamera * _this, int);
};

extern CCamera &TheCamera;