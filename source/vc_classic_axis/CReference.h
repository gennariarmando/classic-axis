#pragma once

class CEntity;

class CReference {
public:
	CReference *m_pNext;
	CEntity **m_ppEntity;
};

VALIDATE_SIZE(CReference, 8);