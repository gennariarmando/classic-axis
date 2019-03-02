#pragma once
#include "CShadowCamera.h"
#include "RenderWare.h"

class CCutsceneShadow {
public:
	CShadowCamera m_Camera;
	bool m_bResample;
	char _pad0[3];
	CShadowCamera m_ResampleCamera;
	int m_nBlurPasses;
	CShadowCamera m_BlurCamera;
	bool m_bGradient;
	char _pad1[3];
	CShadowCamera m_GradientCamera;
	RpAtomic *m_pAtomic;
	int m_nRwObjectType;
	RpLight *m_pLight;
	RwSphere m_BoundingSphere;
	RwSphere m_BaseSphere;
};

VALIDATE_SIZE(CCutsceneShadow, 0x58);