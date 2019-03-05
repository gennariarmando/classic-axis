#include "CGTAVC.h"
#include "CWeaponInfo.h"

CWeaponInfo(&aWeaponInfo)[37] = *(CWeaponInfo(*)[37])*(int *)0x782A14;
char **CWeaponInfo::ms_aWeaponNames = (char **)0x603334;

CWeaponInfo* CWeaponInfo::GetWeaponInfo(eWeaponType weaponType) {
	return ((CWeaponInfo*(__cdecl *)(eWeaponType))0x5D5710)(weaponType);

}