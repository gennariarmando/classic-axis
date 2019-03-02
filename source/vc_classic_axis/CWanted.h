#pragma once
#include "CVector.h"
#include "CEntity.h"

enum eCrimeType : __int32 {
	CRIME_NONE = 0x0,
	CRIME_SHOT_FIRED = 0x1,
	CRIME_PED_FIGHT = 0x2,
	CRIME_COP_FIGHT = 0x3,
	CRIME_DAMAGED_PED = 0x4,
	CRIME_DAMAGED_COP = 0x5,
	CRIME_CAR_THEFT = 0x6,
	CRIME_CRIME7 = 0x7,
	CRIME_COP_EVASIVE_DIVE = 0x8,
	CRIME_COP_EVASIVE_DIVE2 = 0x9,
	CRIME_PED_RUN_OVER = 0xA,
	CRIME_COP_RUN_OVER = 0xB,
	CRIME_DESTROYED_HELI = 0xC,
	CRIME_PED_BURNED = 0xD,
	CRIME_COP_BURNED = 0xE,
	CRIME_VEHICLE_BURNED = 0xF,
	CRIME_DESTROYED_CESSNA = 0x10,
};

#include "CPed.h"

enum eCopType : unsigned int {
	COP_TYPE_COP,
	COP_TYPE_FBI,
	COP_TYPE_SWAT1,
	COP_TYPE_SWAT2,
	COP_TYPE_ARMY,
	COP_TYPE_VICE

};

class CHeli;
class CStinger;

class CCopPed : public CPed {
public:
	int field_5F4;
	float field_5F8;
	char field_5FC;
	char field_5FD;
	char field_5FE;
	char field_5FF;
	char field_600;
	char field_601;
	char field_602;
	char field_603; // padding?
	float fAbseilPos; //current abseil position (on the rope)
	unsigned int nCopType; //type of the cop, 0-4 (3 - descending from rope)
	bool bThrowsSpikeTrap; //if this is set, the cop will throw a spike trap as soon as it can
private:
	char _pad1[3]; // 1549-1552
public:
	CHeli* pHeliAbseil; //pointer to the heli this cop is abseiling from
	unsigned int dwRopeIdentifier; // swat rope (CRopes)
	int field_618;
	int field_61C;
	CStinger *m_pStinger; // CStinger object
	int field_624;
	char field_628;
private:
	char _pad4[3];
public:

};

VALIDATE_SIZE(CCopPed, 0x62C);

class CCrimeBeingQd {
public:
	eCrimeType m_nCrimeType;
	CEntity* pVictim; //entity who was the victim of the crime
	unsigned int m_nStartTime;
	CVector m_vecCoors;
	bool m_bAlreadyReported;
	bool m_bPoliceDontReallyCare;
	char pad[2];

	// [FrogByteDQ]: TODO: move this to CCrimeBeingQd.h file
	// [FrogByteDQ]: TODO: constructor sub_5388D0
};

VALIDATE_SIZE(CCrimeBeingQd, 0x1C);

class CWanted {
public:
	unsigned int m_nChaosLevel; //amount of wanted points
	unsigned int m_nChaosLevelBeforeParole;  //minimum amount of points, not used
	unsigned int m_nLastTimeWantedDecreased;
	unsigned int m_nLastTimeWantedLevelChanged;
	unsigned int m_dwTimeOfParole;
	float m_fMultiplier;
	unsigned char m_nCopsInPursuit;
	unsigned char m_nMaxCopsInPursuit;
	unsigned char m_nMaxCopCarsInPursuit;
	unsigned char m_nCopsBeatingSuspect;
	unsigned short m_nChanceOnRoadBlock;
	union
	{
		unsigned char m_nWantedFlags;
		struct
		{
			unsigned char b0 : 1;
			unsigned char b1 : 1;
			unsigned char m_bSwatRequired : 1;
			unsigned char m_bFbiRequired : 1;
			unsigned char m_bArmyRequired : 1;
		};
	};
	char _pad0[1];
	unsigned int m_nWantedLevel;
	unsigned int m_nWantedLevelBeforeParole;
	CCrimeBeingQd m_asCrimesBeingQd[16];
	class CCopPed *m_apCopsInPursuit[10];

	//variables
	static int &nMaximumWantedLevel; // 9600
	static int &MaximumWantedLevel;  // 6
};

VALIDATE_SIZE(CWanted, 0x210);