#pragma once
#include "CEntity.h"
#include "CEntryInfoList.h"
/*
class CDummy : public CEntity {
protected:
	CDummy() : CEntity() {}
public:

	CEntryInfoList m_collisionList;

	//funcs
	CDummy();
	static void* operator new(unsigned int size);
	static void operator delete(void* data);

	CDummy(const CDummy &) = delete;
	CDummy &operator=(const CDummy &) = delete;
};

VALIDATE_SIZE(CDummy, 0x68);*/