#pragma once

#include "RenderWare.h"

enum ModelInfoType {
	MODEL_INFO_SIMPLE = 1,
	MODEL_INFO_TIME = 3,
	MODEL_INFO_WEAPON = 4,
	MODEL_INFO_CLUMP = 5,
	MODEL_INFO_VEHICLE = 6,
	MODEL_INFO_PED = 7
};

class C2dEffect;
class CColModel;

// originally an abstract class
class CBaseModelInfo {
public:
	char           m_szName[21];
	unsigned char  m_nType; // see ModelInfoType
	unsigned char  m_nNum2dEffects;
	bool           m_bDoWeOwnTheColModel;
	CColModel     *m_pColModel;
	short          m_n2dEffectIndex;
	short          m_nObjectDataIndex;
	unsigned short m_nRefCount;
	short          m_nTxdIndex;

	virtual ~CBaseModelInfo() {}

protected:
	CBaseModelInfo() {};
	CBaseModelInfo(const CBaseModelInfo &) {};
	CBaseModelInfo &operator=(const CBaseModelInfo &) { return *this; };
};

VALIDATE_SIZE(CBaseModelInfo, 0x28);