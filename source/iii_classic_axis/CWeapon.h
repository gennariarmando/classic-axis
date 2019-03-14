#pragma once

#include "eWeaponType.h"
#include "CAutomobile.h"

enum eWeaponState : unsigned int {
	WEAPONSTATE_READY,
	WEAPONSTATE_FIRING,
	WEAPONSTATE_RELOADING,
	WEAPONSTATE_OUT_OF_AMMO
};

class CWeapon {
public:
	eWeaponType m_nType;
	eWeaponState m_nState;
	unsigned int m_nAmmoInClip;
	unsigned int m_nTotalAmmo;
	unsigned int m_nNextShotTime;
	bool m_bAddRotOffset;
private:
	char _pad15[3];
};

VALIDATE_SIZE(CWeapon, 0x18);
