#pragma once

#include "CVector.h"

class CVehicle;

class CDoor {
public:
	float         m_fOpenAngle;
	float         m_fClosedAngle;
	unsigned char m_bDirn;
	unsigned char m_bAxis;
	unsigned char m_bState;
private:
	char _padB;
public:
	float			m_fAngle;
	float			m_fPrevAngle;
	float			m_fAngVel;
	CVector			vecVelocity;
};

VALIDATE_SIZE(CDoor, 0x24);