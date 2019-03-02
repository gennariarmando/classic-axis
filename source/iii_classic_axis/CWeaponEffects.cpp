#include "CGTA3D.h"
#include "CWeaponEffects.h"

CWeaponEffects &gCrosshair = *(CWeaponEffects *)0x6503BC;

void CWeaponEffects::MarkTarget(CVector TargetPosition, CRGBA color, float fSize) {
	gCrosshair.m_bCrosshair = true;
	gCrosshair.m_vecPos = TargetPosition;
	gCrosshair.m_Color = color;
	gCrosshair.m_fSize = fSize;
}
