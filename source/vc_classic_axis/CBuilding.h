#pragma once
#include "CEntity.h"

class CBuilding : public CEntity {
protected:
	CBuilding() : CEntity() {}
public:

};

VALIDATE_SIZE(CBuilding, 0x64);