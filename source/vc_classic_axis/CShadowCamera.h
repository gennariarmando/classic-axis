#pragma once
#include "RenderWare.h"

class CShadowCamera {
public:
	RwCamera *m_pShadowCamera;
	RwTexture *m_pShadowRenderTexture;
};

VALIDATE_SIZE(CShadowCamera, 0x08);