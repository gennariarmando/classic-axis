#pragma once

#include "CVector.h"
#include "CSphere.h"

class CBox {
public:
	CVector m_vecMin;
	CVector m_vecMax;
};

VALIDATE_SIZE(CBox, 0x18);

struct tColSurface {
	unsigned char material;
	unsigned char flag;
	unsigned char lighting;
	unsigned char light;
};

VALIDATE_SIZE(tColSurface, 0x4);

class CColBox : public CBox {
public:
	tColSurface m_surface;
};

VALIDATE_SIZE(CColBox, 0x1C);

class CColSphere : public CSphere {
public:
	tColSurface m_surface;

};

VALIDATE_SIZE(CColSphere, 0x14);

class CColLine {
public:
	CVector m_vecStart;
	char field_C[4];
	CVector m_vecEnd;
	char field_1C[4];

};

VALIDATE_SIZE(CColLine, 0x20);

class CColTriangle {
public:
	unsigned short m_nVertA; // vertex index in vertices array
	unsigned short m_nVertB; // vertex index in vertices array
	unsigned short m_nVertC; // vertex index in vertices array
	unsigned char m_nMaterial;
	unsigned char m_nLight;
};

VALIDATE_SIZE(CColTriangle, 0x8);

class CColTrianglePlane {
public:
	CVector m_vecNormal;
	float m_fDistance;
	unsigned char m_nOrientation;
private:
	char _pad11[3];

};

VALIDATE_SIZE(CColTrianglePlane, 0x14);

class CColPoint {
public:
	CVector  m_vPoint;
	float field_C;
	CVector m_vNormal;
	float field_1C;
	unsigned char m_nSurfaceTypeA;
	unsigned char m_nPieceTypeA;
	unsigned char m_nSurfaceTypeB;
	unsigned char m_nPieceTypeB;
	int field_24;
};

VALIDATE_SIZE(CColPoint, 0x28);

class CColModel {
public:
	CColSphere m_boundSphere;
	CColBox m_boundBox;
	unsigned short m_nNumOfSpheres;
	unsigned short m_nNumOfLines;
	unsigned short m_nNumOfBoxes;
	unsigned short m_nNumOfTriangles;
	unsigned int m_nColLevel;
	unsigned char m_nFlags;
private:
	char _pad3D[3];
public:
	CColSphere *m_pSpheres;
	CColLine *m_pLines;
	CColBox *m_pBoxes;
	CVector *m_pVertices;
	CColTriangle *m_pTriangles;
	CColTrianglePlane *m_pTrianglePlanes;
};

VALIDATE_SIZE(CColModel, 0x58);