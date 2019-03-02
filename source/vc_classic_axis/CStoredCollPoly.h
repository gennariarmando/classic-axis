#pragma once

#include "CVector.h"

class CStoredCollPoly {
public:
	CVector m_aVertices[3]; // triangle vertices
	bool m_bIsActual;
private:
	char _pad[3];
};

VALIDATE_SIZE(CStoredCollPoly, 0x28);