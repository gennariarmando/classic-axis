#pragma once

#include "tTransmissionGear.h"

class cTransmission {
public:
	tTransmissionGear m_aGears[6];
	unsigned char   m_nDriveType; // F/R/4
	unsigned char   m_nEngineType; // P/D/E
	unsigned char   m_nNumberOfGears; // 1 to 6
	unsigned char m_nHandlingFlags;
	float             m_fEngineAcceleration; // 0.1 to 10.0
	float             m_fMaxGearVelocity; // 5.0 to 150.0
	float             m_fMaxSpeed;
	float             m_fMinGearVelocity;
	float             m_fCurrentSpeed;
};

VALIDATE_SIZE(cTransmission, 0x60);