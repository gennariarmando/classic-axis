#pragma once

class CNodeAddress {
public:
	short m_wAreaId;
	short m_wNodeId;

	CNodeAddress() : m_wAreaId(-1), m_wNodeId(-1) {}
};

VALIDATE_SIZE(CNodeAddress, 0x4);

class CCarPathLinkAddress {
public:
	short m_wCarPathLinkId : 10;
	short m_wAreaId : 6;
};

VALIDATE_SIZE(CCarPathLinkAddress, 0x2);

class CPathFind {
public:

};

extern CPathFind& ThePaths;