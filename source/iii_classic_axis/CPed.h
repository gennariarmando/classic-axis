#pragma once
#include "RenderWare.h"
#include "CPhysical.h"
#include "CStoredCollPoly.h"
#include "CPedIK.h"
#include "CPathNode.h"
#include "CPedStats.h"
#include "CWeapon.h"
#include "ePedState.h"
#include "CPlayerPed.h"

enum eMoveState {
	PEDMOVE_NONE,
	PEDMOVE_STILL,
	PEDMOVE_WALK,
	PEDMOVE_RUN,
	PEDMOVE_SPRINT
};

class CVehicle;

class CPed : public CPhysical {
protected:
	CPed() : CPhysical(), m_aWeapons{ } {}
public:
	CStoredCollPoly m_polyColliding;
	float m_fCollisionSpeed;
	struct {
		unsigned char b01 : 1;
		unsigned char b02 : 1;
		unsigned char b03 : 1;
		unsigned char b04 : 1;
		unsigned char b05 : 1;
		unsigned char b06 : 1;
		unsigned char b07 : 1;
		unsigned char b08 : 1;

		unsigned char b09 : 1;
		unsigned char b10 : 1;
		unsigned char b11 : 1;
		unsigned char b12 : 1;
		unsigned char b13 : 1;
		unsigned char b14 : 1;
		unsigned char b15 : 1;
		unsigned char b16 : 1;

		unsigned char b17 : 1;
		unsigned char b18 : 1;
		unsigned char b19 : 1;
		unsigned char b20 : 1;
		unsigned char b21 : 1;
		unsigned char b22 : 1;
		unsigned char b23 : 1;
		unsigned char b24 : 1;

		unsigned char b25 : 1;
		unsigned char b26 : 1;
		unsigned char b27 : 1;
		unsigned char b28 : 1;
		unsigned char b29 : 1;
		unsigned char b30 : 1;
		unsigned char b31 : 1;
		unsigned char b32 : 1;

		unsigned char b33 : 1;
		unsigned char b34 : 1;
		unsigned char b35 : 1;
		unsigned char b36 : 1;
		unsigned char b37 : 1;
		unsigned char b38 : 1;
		unsigned char b39 : 1;
		unsigned char b40 : 1;

		unsigned char b41 : 1;
		unsigned char b42 : 1;
		unsigned char b43 : 1;
		unsigned char b44 : 1;
		unsigned char b45 : 1;
		unsigned char b46 : 1;
		unsigned char b47 : 1;
		unsigned char b48 : 1;

		unsigned char b49 : 1;
		unsigned char b50 : 1;
		unsigned char b51 : 1;
		unsigned char b52 : 1;
		unsigned char b53 : 1;
		unsigned char b54 : 1;
		unsigned char b55 : 1;
		unsigned char b56 : 1;

		unsigned char b57 : 1;
		unsigned char b58 : 1;
		unsigned char b59 : 1;
		unsigned char b60 : 1;
		unsigned char b61 : 1;
		unsigned char b62 : 1;
		unsigned char b63 : 1;
		unsigned char b64 : 1;

		unsigned char b65 : 1;
		unsigned char b66 : 1;
		unsigned char b67 : 1;
		unsigned char b68 : 1;
		unsigned char b69 : 1;
		unsigned char b70 : 1;
		unsigned char b71 : 1;
		unsigned char b72 : 1;
	} m_nPedFlags;
	char field_15D;
	char field_15E;
	char field_15F;
	unsigned char m_nPedStatus;
private:
	char _pad161[3];
public:
	int m_nObjective;
	int m_nPrevObjective;
	CEntity *m_pObjectiveEntity;
	CVehicle *m_pObjectiveVehicle;
	CVector m_vObjective;
	CPed *m_pGangLeader;
	int m_nPedFormation;
	unsigned int m_nFearFlags;
	CEntity *m_pThreatEntity;
	float m_fEventOrThreatX;
	float m_fEventOrThreatY;
	unsigned int m_nEventType;
	CEntity *m_pEventEntity;
	float m_fAngleToEvent;
	AnimBlendFrameData *m_pBodyParts[12];
	int m_nAnimGroupId;
	void *m_pVehicleAnim;
	CVector2D m_vAnimMoveDelta;
	CVector m_vOffsetSeek;
	CPedIK m_pedIK;
	float m_fActionX;
	float m_fActionY;
	int m_nActionTimer;
	ePedState m_eState;
	ePedState m_nLastAction;
	eMoveState m_nMoveState;
	eMoveState m_eCurrentMoveState;
	eMoveState m_ePreviousMoveState;
	int m_nWaitState;
	int m_nWaitTimer;
	CPathNode *m_apPathNodesStates[8];
	CPathNode m_aPathNodeStates[10];
	unsigned short m_nPathNodes;
	short m_nCurPathNode;
	char m_nPathState;
private:
	char _pad2B5[3];
public:
	CPathNode *m_pNextPathNode;
	CPathNode *m_pLastPathNode;
	float m_fHealth;
	float m_fArmour;
	short m_nRouteLastPoint;
	unsigned short m_nRoutePoints;
	short m_nRoutePos;
	unsigned short m_nRouteType;
	short m_nRouteCurDir;
private:
	char _pad2D2[2];
public:
	float m_fMovedX;
	float m_fMovedY;
	float m_fRotationCur;
	float m_fRotationDest;
	float m_fHeadingRate;
	unsigned short m_nEnterType;
	unsigned short m_nWalkAroundType;
	CPhysical *m_pCurPhysSurface;
	CVector m_vOffsetFromPhysSurface;
	CEntity *m_pCurSurface;
	CVector m_vSeekVehicle;
	CEntity *m_pSeekTarget;
	CVehicle *m_pVehicle;
	bool m_bInVehicle;
private:
	char _pad315[3];
public:
	float m_fSeatPrecisionX;
	bool m_bHasPhone;
private:
	char _pad31D;
public:
	short m_nPhoneId;
	int m_nLookingForPhone;
	int m_nPhoneTalkTimer;
	void *m_pLastAccident;
	unsigned int m_nPedType;
	CPedStats *m_pPedStats;
	float m_fFleeFromPosX;
	float m_fFleeFromPosY;
	void *m_pFleeFrom;
	int m_nFleeTimer;
	void *m_pLastThreatAt;
	int m_nLastThreatTimer;
	CVehicle *m_pVehicleColliding;
	unsigned char m_nStateUnused;
private:
	char _pad351[3];
public:
	int m_nTimerUnused;
	void *m_pTargetUnused;
	CWeapon m_aWeapons[13];
	int dword494;
	unsigned char m_nWepSlot;
	unsigned char byte_499;
	unsigned char m_nWepSkills;
	unsigned char m_nWepAccuracy;
	CEntity *m_pPointGunAt;
	CVector m_vHitLastPos;
	int m_nHitCounter;
	int m_nLastHitState;
	void *m_pPedFire;
	CEntity* m_pLookAimEntity;
	float m_fLookDirection;
	int m_nWepModelID;
	int m_nLeaveCarTimer;
	int m_nGetUpTimer;
	int m_nLookTimer;
	int m_nStandardTimer;
	int m_nAttackTimer;
	int m_nLastHitTime;
	int m_nHitRecoverTimer;
	int m_nObjectiveTimer;
	int m_nDuckTimer;
	int m_nDuckAndCoverTimer;
	int m_nBloodyTimer;
	unsigned char m_nPanicCounter;
	unsigned char m_nDeadBleeding;
	unsigned char m_nBodyPartBleeding;
private:
	char _pad4F3;
public:
	CPed *m_apNearPeds[10];
	unsigned short m_nNumNearPeds;
	unsigned char m_nLastDamWep;
private:
	char _pad51F;
public:
	int m_nTalkTimerLast;
	int m_nTalkTimer;
	short m_nTalkTypeLast;
	unsigned short m_nTalkType;
	CVector m_vSeekPosEx;
	float m_fSeekExAngle;

public:
	bool BeQuiteAndEasy();
	bool CanWeRunAndFireWithWeapon();
	bool CanStrafeOrMouseControl();
	void SetAimFlag(float heading);
	char ClearLookFlag();
	void SetPointGunAt(CEntity *entity);
	void AimGun();
	void ClearPointGunAt();
	void ClearAimFlag();
	void ClearAll();
	void RestorePreviousState();
	int SetAttackTimer(unsigned int time);
	int SetShootTimer(unsigned int time);
	void Say(unsigned short arg0);


public:
	static bool m_bDoAiming;
	static bool m_bHideCrosshair;

};

VALIDATE_SIZE(CPed, 0x53C);