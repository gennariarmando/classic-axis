#pragma once

class CPathNode {
public:
	short m_wPathData;
	short m_wPosX;
	short m_wPosY;
	short m_wPosZ;
};

VALIDATE_SIZE(CPathNode, 0x8);