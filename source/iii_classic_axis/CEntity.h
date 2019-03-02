#pragma once
#include "CPlaceable.h"
#include "CRect.h"
#include "RenderWare.h"

class CReference;

class CEntity : public CPlaceable {
public:
	union {
		RwCamera *m_pRwObject;
		RpAtomic *m_pRwAtomic;
		RpClump  *m_pRwClump;
	};

	unsigned char m_nType : 3;
	unsigned char m_nState : 5;

	struct {
		unsigned char bUsesCollision : 1;
		unsigned char bCollisionProcessed : 1;
		unsigned char bIsStatic : 1;
		unsigned char b04 : 1;
		unsigned char b05 : 1;
		unsigned char b06 : 1;
		unsigned char bIsInSafePosition : 1;
		unsigned char bHasContacted : 1;

		unsigned char b09 : 1;
		unsigned char bExplosionProof : 1;
		unsigned char bIsVisible : 1;
		unsigned char b12 : 1;
		unsigned char b13 : 1;
		unsigned char bFlashing : 1;
		unsigned char bIsBIGBuilding : 1;
		unsigned char bRenderDamaged : 1;

		unsigned char bBulletProof : 1;
		unsigned char bFireProof : 1;
		unsigned char bCollisionProof : 1;
		unsigned char bMeleeProof : 1;
		unsigned char bOnlyDamagedByPlayer : 1;
		unsigned char b22 : 1;
		unsigned char b23 : 1;
		unsigned char b24 : 1;

		unsigned char b25 : 1;
		unsigned char bHasHitWall : 2;
		unsigned char bImBeingRendered : 1;
		unsigned char b28 : 1;
		unsigned char b29 : 1;
		unsigned char bDrawLast : 1;
		unsigned char b31 : 1;
		unsigned char b32 : 1;

		unsigned char b33 : 1;
		unsigned char b34 : 2;
	} m_nFlags;
private:
	char _pad[2];
public:
	unsigned short m_nScanCode;
	unsigned short m_nRandomSeed;
	short m_nModelIndex;
	short m_nLevel; // -1 - ignore level transitions
	CReference *m_pFirstRef;

protected:
	CEntity() : CPlaceable() {}

public:

	inline CVector &GetPosition() {
		return m_matrix.pos;
	}

	/*inline CVector TransformFromObjectSpace(CVector const& offset) {
		return this->m_matrix * offset;
	}*/

	CEntity(const CEntity &) = delete;
	CEntity &operator=(const CEntity &) = delete;
};

VALIDATE_SIZE(CEntity, 0x64);