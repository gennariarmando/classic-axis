#pragma once

#include "RenderWare.h"

class CScene {
public:
	RpWorld *m_pWorld;
	RwCamera *m_pCamera;
};

extern CScene &Scene;