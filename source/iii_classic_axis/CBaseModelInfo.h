#pragma once

#include "RenderWare.h"

enum ModelInfoType {
	MODEL_INFO_SIMPLE = 1,
	MODEL_INFO_MLO = 2,
	MODEL_INFO_TIME = 3,
	MODEL_INFO_CLUMP = 4,
	MODEL_INFO_VEHICLE = 5,
	MODEL_INFO_PED = 6,
	MODEL_INFO_XTRACOMPS = 7
};

class C2dEffect;
class CColModel;

// originally an abstract class
class CBaseModelInfo {
public:
	char           m_szName[24];
	CColModel     *m_pColModel;
	C2dEffect     *m_p2dEffect;
	short          m_nObjectDataIndex;
	unsigned short m_nRefCount;
	short          m_nTxdIndex;
	unsigned char  m_nType; // see ModelInfoType
	unsigned char  m_nNum2dEffects;
	bool           m_bDoWeOwnTheColModel;
private:
	char _pad2D[3];
public:
	virtual ~CBaseModelInfo() {}

protected:
	CBaseModelInfo() {};
	CBaseModelInfo(const CBaseModelInfo &) {};
	CBaseModelInfo &operator=(const CBaseModelInfo &) { return *this; };
};

VALIDATE_SIZE(CBaseModelInfo, 0x30);
