#pragma once
#include "RenderWare.h"
#include "CRect.h"
#include "CRGBA.h"

class CSprite {
public:
	//static bool CalcScreenCoors(RwV3d const& posn, RwV3d *out, float *w, float *h, bool checkMaxVisible);
};

class CSprite2d {
public:
	RwTexture *m_pTexture;
	static int &mBankStart;
	static RwIm2DVertex *maBankVertices;
	static int &mCurrentBank;
	static CSprite2d *mCurrentSprite;
	static float &RecipNearClip;
	static RwTexture *mpBankTextures;
	static RwIm2DVertex *maVertices; // static RwIm2DVertex maVertices[8]

public:
	void Delete();
	void SetTexture(const char* name);
	void Draw(CRect const & posn, CRGBA const & color);
	void Draw(float x, float y, float w, float h, CRGBA const & color);
	void Draw(CRect const & posn, CRGBA const & color, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);
	void SetVertices(CRect const& posn, CRGBA const& color1, CRGBA const& color2, CRGBA const& color3, CRGBA const& color4, unsigned int numVerts);
	void SetVertices(CRect const & posn, CRGBA const & color1, CRGBA const & color2, CRGBA const & color3, CRGBA const & color4, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);

public:
	static void InitPerFrame();
	static void SetRecipNearClip();
	static void DefinedState();
	static void DrawRect(CRect const& posn, CRGBA const& color);
	static int GetBank(int arg0, RwTexture* texture);
	static void DrawBank(int arg0);
};