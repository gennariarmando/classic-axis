#pragma once

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