#pragma once

#include "CVector.h"

class CWheel {
public:
	CVector vecWheelPos;
	char __p000C[4];
	CVector vecWheelAngle;
	char __p001C[12];
};

VALIDATE_SIZE(CWheel, 0x28);