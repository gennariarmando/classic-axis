#pragma once

class CPathNode {
public:
	short m_wPathData1;
	short m_wPathData2;
	short m_wPosX;
	short m_wPosY;
	short m_wPosZ;
	char field_A[2];
	short field_C;
	char field_E[6];
};

VALIDATE_SIZE(CPathNode, 0x14);