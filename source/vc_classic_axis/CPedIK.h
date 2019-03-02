#pragma once
#include "RenderWare.h"

// Return flags from MoveLimb() function
enum MoveLimbResult
{
	CANT_REACH_TARGET,
	HAVENT_REACHED_TARGET,
	REACHED_TARGET
};

struct LimbOrientation
{
public:
	float m_fYaw;
	float m_fPitch;
};
VALIDATE_SIZE(LimbOrientation, 0x8);

struct LimbMovementInfo
{
	float maxYaw, minYaw;
	float yawD;
	float maxPitch, minPitch;
	float pitchD;
};
VALIDATE_SIZE(LimbMovementInfo, 0x18);

class CPed;

class CPedIK {
public:
	CPed * m_pPed;
	LimbOrientation m_aLimbOrien[2];
	float m_fSlopePitch;
	float m_fSlopePitchLimitMult;
	float m_fSlopeRoll;
	float m_fBodyRoll;

	union
	{
		unsigned int m_nFlags;
		struct
		{
			unsigned int bGunReachedTarget : 1;
			unsigned int bTorsoUsed : 1;
			unsigned int bUseArm : 1;
			unsigned int bSlopePitch : 1;
		};
	};

public:
	RwMatrix *GetComponentPosition(RwV3d * pos, int id);
	char PointGunInDirection(float phi, float theta);
	char PointGunAtPosition(CVector const& posn);

};

VALIDATE_SIZE(CPedIK, 0x28);
