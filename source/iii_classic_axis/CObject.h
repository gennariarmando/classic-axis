#pragma once

#include "CPhysical.h"
#include "CDummyObject.h"

enum eObjectType {
	OBJECT_NA = 0,
	OBJECT_MAP = 1,
	OBJECT_MISSION = 2,
	OBJECT_TEMPORARY = 3,
	OBJECT_CUTSCENE = 4,
	OBJECT_STINGER = 5
};

class CObject : public CPhysical {
public:
	CMatrix m_mObjectCoords;
	float m_fUprootLimit;
	unsigned char  m_nObjectType;
	unsigned char  m_nObjectFlags;
	char field_176;
private:
	char _pad177;
public:
	float m_fCollisionDamageMultiplier;
	char m_nCollisionDamageEffect;
	bool m_bSpecialCollisionResponseCases;
	bool m_bCameraToAvoidThisObject;
	char field_17F;
	char field_180;
	char field_181;
	char field_182;
	char field_183;
	int field_184;
	short m_nFlyingObjectModelId;

private:
	char _pad18A[2];

public:
	CEntity *m_pRoad;
	int field_190;
	unsigned char  m_nColorId[2];
	char field_196[2];

};

VALIDATE_SIZE(CObject, 0x198);