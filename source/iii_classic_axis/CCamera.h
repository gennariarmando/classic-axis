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
	bool m_bJustCameOutOfGarage;
	bool m_bJustInitalised;
	bool m_bJust_Switched;
	bool m_bLookingAtPlayer;
	bool m_bLookingAtVector;
	bool m_bMoveCamToAvoidGeom;
	bool m_bObbeCinematicPedCamOn;
	bool m_bObbeCinematicCarCamOn;
	bool m_bRestoreByJumpCut;
	bool m_bUseNearClipScript;
	bool m_bStartInterScript;
	bool m_bStartingSpline;
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
	bool m_bFailedCullZoneTestPreviously;
	bool m_FadeTargetIsSplashScreen;
	bool WorldViewerBeingUsed;
	__int8 ActiveCam;
	__int32 m_uiCamShakeStart;
	__int32 m_uiFirstPersonCamLastInputTime;
	__int32 m_uiLongestTimeInMill;
	__int32 m_uiNumberOfTrainCamNodes;
	__int8   m_uiTransitionJUSTStarted;
	__int8   m_uiTransitionState;
	__int32 m_uiTimeLastChange;
	__int32 m_uiTimeWeEnteredIdle;
	__int32 m_uiTimeTransitionStart;
	__int32 m_uiTransitionDuration;
	int m_BlurBlue;
	int m_BlurGreen;
	int m_BlurRed;
	int m_BlurType;
	__int32 unk;
	int m_iWorkOutSpeedThisNumFrames;
	int m_iNumFramesSoFar;
	int m_iCurrentTrainCamNode;
	int m_motionBlur;
	int m_imotionBlurAddAlpha;
	int m_iCheckCullZoneThisNumFrames;
	int m_iZoneCullFrameNumWereAt;
	int WhoIsInControlOfTheCamera;
	float CamFrontXNorm;
	float CamFrontYNorm;
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
	float m_fPedZoomValueScript;
	float m_fPedZoomValueSmooth;
	float m_fPositionAlongSpline;
	float m_ScreenReductionPercentage;
	float m_ScreenReductionSpeed;
	float m_AlphaForPlayerAnim1rstPerson;
	float Orientation;
	float PedZoomIndicator;
	float PlayerExhaustion;
	float SoundDistUp, SoundDistLeft, SoundDistRight;
	float SoundDistUpAsRead, SoundDistLeftAsRead, SoundDistRightAsRead;
	float SoundDistUpAsReadOld, SoundDistLeftAsReadOld, SoundDistRightAsReadOld;
	float m_fWideScreenReductionAmount;
	float m_fStartingFOVForInterPol;
	float m_fMouseAccelHorzntl;
	float m_fMouseAccelVertical;
	float m_f3rdPersonCHairMultX;
	float m_f3rdPersonCHairMultY;
	CCam Cams[3];
	void *pToGarageWeAreIn;
	void *pToGarageWeAreInForHackAvoidFirstPerson;
	CQueuedMode m_PlayerMode;
	CQueuedMode PlayerWeaponMode;
	CVector m_PreviousCameraPosition;
	CVector m_RealPreviousCameraPosition;
	CVector m_cvecAimingTargetCoors;
	CVector m_vecFixedModeVector;
	CVector m_vecFixedModeSource;
	CVector m_vecFixedModeUpOffSet;
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
	CVector SourceDuringInter;
	CVector TargetDuringInter;
	CVector UpDuringInter;
	RwCamera *m_pRwCamera;
	CEntity *pTargetEntity;
	CCamPathSplines m_arrPathArray[4];
	CTrainCamNode m_arrTrainCamNode[800];
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
	float m_fFractionInterToStopMovingTarget;
	float m_fFractionInterToStopCatchUpTarget;
	float m_fGaitSwayBuffer;
	float m_fScriptPercentageInterToStopMoving;
	float m_fScriptPercentageInterToCatchUp;
	__int32 m_fScriptTimeForInterPolation;
	__int16 m_iFadingDirection;
	int m_iModeObbeCamIsInForCar;
	__int16 m_iModeToGoTo;
	__int16 m_iMusicFadingDirection;
	__int16 m_iTypeOfSwitch;
	__int32 m_uiFadeTimeStarted;
	__int32 m_uiFadeTimeStartedMusic;

public:
	static char &m_nFadeColorsSet;
	static char &m_bUseMouse3rdPerson;

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
	static void __fastcall	Process(CCamera * _this, int);
};

extern CCamera &TheCamera;