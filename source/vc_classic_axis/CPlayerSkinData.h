#pragma once

class CPlayerSkinData {
public:
	int m_nId;
	unsigned __int8 m_aName[256];
	unsigned __int8 m_aOriginalPath[256];
	unsigned __int8 m_aDateInfo[256];
	CPlayerSkinData *m_pNext;
};