#include "CGTAVC.h"
#include "CWeaponInfo.h"

CWeaponInfo(&aWeaponInfo)[14] = *(CWeaponInfo(*)[14])*(int *)0x6503EC;
char **CWeaponInfo::ms_aWeaponNames = (char **)0x603334;

CWeaponInfo* CWeaponInfo::GetWeaponInfo(eWeaponType weaponType) {
	return ((CWeaponInfo*(__cdecl *)(eWeaponType))0x564FD0)(weaponType);

}