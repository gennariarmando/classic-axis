#pragma once

#include "CEntity.h"
#include "CSector.h"
#include "CEntryInfoList.h"
#include "CCol.h"

class CPhysical : public CEntity {
public:
	void           *m_nAudioEntityId;
	float field_68;
	int field_6C;
	int field_70;
	int             m_nLastTimeCollided;
	CVector         m_vecMoveSpeed;
	CVector         m_vecTurnSpeed;
	CVector         m_vecFrictionMoveForce;
	CVector         m_vecFrictionTurnForce;
	CVector         m_vecForce;
	CVector         m_vecTorque;
	float           m_fMass;
	float           m_fTurnMass;
	float           m_fVelocityFrequency;
	float           m_fAirResistance;
	float           m_fElasticity;
	float           m_fBuoyancy;
	CVector         m_vecCentreOfMass;
	CEntryInfoList  m_collisionList;
	CPtrNode       *m_pMovingListNode;
	char field_EC;
	char field_ED;
	unsigned char   m_nNumCollisionRecords;
	char field_EF;
	CEntity        *m_apCollisionRecords[6];
	float           m_fTotSpeed;
	float           m_fCollisionPower;
	CPhysical      *m_pPhysColliding;
	CVector         m_vecCollisionPower;
	short           m_nComponentCol;
	unsigned char   m_nMoveFlags;
	unsigned char   m_nLastCollType;
	unsigned char   m_nZoneLevel;
private:
	char _pad125[3];
public:

protected:
	CPhysical() : CEntity() {}

	//CPhysical() = delete;
	CPhysical(const CPhysical &) = delete;
	CPhysical &operator=(const CPhysical &) = delete;
};

VALIDATE_SIZE(CPhysical, 0x128);