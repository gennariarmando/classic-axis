#pragma once

#include "eWeaponType.h"
#include "CAutomobile.h"

class CWeapon {
public:
	eWeaponType m_nType;
	unsigned int m_nState;
	unsigned int m_nAmmoInClip;
	unsigned int m_nTotalAmmo;
	unsigned int m_nNextShotTime;
	bool m_bAddRotOffset;
private:
	char _pad15[3];
};

VALIDATE_SIZE(CWeapon, 0x18);
