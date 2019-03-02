#pragma once
#include "CVector.h"

class CSphere {
public:
	CVector m_vecCenter;
	float   m_fRadius;
};

VALIDATE_SIZE(CSphere, 0x10);