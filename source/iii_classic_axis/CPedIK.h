#pragma once

#include "LimbOrientation.h"
#include "AnimBlendFrameData.h"
#include "eBodyParts.h"

class CPedIK {
public:
	class CPed *m_pPed;
	LimbOrientation m_sHead;
	LimbOrientation m_sTorso;
	LimbOrientation m_sUpperArm;
	LimbOrientation m_sLowerArm;
	unsigned int m_flags;

	// variables
	static LimbMovementInfo *ms_headInfo;
	static LimbMovementInfo *ms_headRestoreInfo;
	static LimbMovementInfo *ms_torsoInfo;
	static LimbMovementInfo *ms_upperArmInfo;
	static LimbMovementInfo *ms_lowerArmInfo;

public:
	static void __fastcall RotateTorso(void *, int, int, int, char);

	RwMatrix *GetComponentPosition(RwV3d * pos, int id);
	char PointGunInDirection(float phi, float theta);
	char PointGunAtPosition(CVector const& posn);

};

VALIDATE_SIZE(CPedIK, 0x28);
