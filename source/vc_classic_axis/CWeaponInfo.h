#pragma once
#include "eWeaponType.h"
#include "CVector.h"

enum eWeaponFire : unsigned int {
	WEAPON_FIRE_MELEE,
	WEAPON_FIRE_INSTANT_HIT,
	WEAPON_FIRE_PROJECTILE,
	WEAPON_FIRE_AREA_EFFECT,
	WEAPON_FIRE_USE
};


class CWeaponInfo {
public:
	eWeaponFire m_eWeaponFire;
	float m_fRange;
	unsigned int m_nFiringRate;
	unsigned int m_nReload;
	unsigned int m_nAmountofAmmunition;
	unsigned int m_nDamage;
	float m_fSpeed;
	float m_fRadius;
	float m_fLifespan;
	float m_fSpread;
	CVector m_vecFireOffset;
	unsigned int m_AnimToPlay; // AssocGroupId m_AnimToPlay;
	unsigned int m_Anim2ToPlay;
	float m_fAnimLoopStart;
	float m_fAnimLoopEnd;
	float m_fAnimFrameFire;
	float m_fAnim2FrameFire;
	int m_nModelId;
	union
	{
		unsigned int m_nWeaponFlags;
		struct
		{
			unsigned char m_bUseGravity : 1;
			unsigned char m_bSlowsDown : 1;
			unsigned char m_bDissipates : 1;
			unsigned char m_bRandSpeed : 1;
			unsigned char m_bExpands : 1;
			unsigned char m_bExplodes : 1;
			unsigned char m_bCanAim : 1;
			unsigned char m_bCanAimWithArm : 1;
			unsigned char m_b1stPerson : 1;
			unsigned char m_bHeavy : 1;
			unsigned char m_bThrow : 1;
		};
	};

	// variables
	// weapon names array
	static char **ms_aWeaponNames; // [14]
	static CWeaponInfo* GetWeaponInfo(eWeaponType weaponType);

};

extern CWeaponInfo(&aWeaponInfo)[37];
