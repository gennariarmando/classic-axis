#pragma once
#include "RenderWare.h"
#include "CVector.h"
#include "CRGBA.h"

class CWeaponEffects {
public:
	char m_bCrosshair;
	char gap_1[3];
	CVector m_vecPos;
	CRGBA m_Color;
	float m_fSize;
	int m_fRotation;

	RwTexture *m_pTexture;
	RwRaster *m_pRaster;
public:
	void MarkTarget(CVector TargetPosition, CRGBA color, float fSize);
};

extern CWeaponEffects &gCrosshair;
