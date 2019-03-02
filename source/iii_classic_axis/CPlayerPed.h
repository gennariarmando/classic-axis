#pragma once
#include "CPed.h"
#include "CWeapon.h"
#include "CPad.h"
#include "CPlayerInfo.h"
#include "CWanted.h"

class CPlayerPed : public CPed {
public:
	CWanted *m_pWanted;
	int *m_pArrestingCop;   //  CCopPed *m_pArrestingCop;
	float m_fMoveSpeed;
	float m_fCurrentStamina;
	float m_fMaxStamina;
	float m_fStaminaProgress;
	char m_bWeaponSlot;
	char m_bSpeedTimerFlag;
	char m_bShouldEvade;
	char field_1367;
	int m_nSpeedTimer;
	int m_nShotDelay;
	float field_1376;
	char field_1380;
	char field_1381;
	char field_1382;
	char field_1383;
	CEntity *m_pEvadingFrom;
	int m_nTargettableObjects[4];
	char m_bAdrenalineActive;
	char m_bHasLockOnTarget;
	char field_1406;
	char field_1407;
	int m_bAdrenalineTime;
	char m_bCanBeDamaged;
	char field_1413;
	char field_1414;
	char field_1415;
	CVector field_1416[6];
	int field_1488[6];
	float field_1512;
	float m_fFPSMoveHeading;

public:
	static void __fastcall ClearWeaponTarget(CPlayerPed *, int);
	bool DoesTargetHaveToBeBroken(CVector arg0, CWeapon* weapon);

};

VALIDATE_SIZE(CPlayerPed, 0x5F0);
