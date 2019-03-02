#include "CGTA3D.h"
#include "CSprite.h"

int &CSprite2d::mBankStart = *(int *)0x774BE8;
RwIm2DVertex *CSprite2d::maBankVertices = (RwIm2DVertex *)0x8429F8;
int &CSprite2d::mCurrentBank = *(int *)0x8F1AF4;
CSprite2d *CSprite2d::mCurrentSprite = (CSprite2d *)0x6F4500;
float &CSprite2d::RecipNearClip = *(float *)0x880DB4;
RwTexture *CSprite2d::mpBankTextures = (RwTexture *)0x774DC0;
RwIm2DVertex *CSprite2d::maVertices = (RwIm2DVertex *)0x6E9168;

static CPatch InjectPatches([](){

});

void CSprite2d::InitPerFrame() {
	((void(__cdecl *)())0x51EAE0)();
}

void CSprite2d::SetRecipNearClip() {
	((void(__cdecl *)())0x51EA20)();
}

void CSprite2d::DefinedState() {
	((void(__cdecl *)())0x526330)();
}

void CSprite2d::SetTexture(const char* name) {
	if (name) {
		if (m_pTexture)
			RwTextureDestroy(m_pTexture);

		m_pTexture = RwTextureRead(name, nullptr);
	}
}

void CSprite2d::Delete() {
	if (m_pTexture) {
		RwTextureDestroy(m_pTexture);
		m_pTexture = nullptr;
	}
}

void CSprite2d::DrawRect(CRect const& posn, CRGBA const& color) {
	((void(__cdecl *)(CRect const& posn, CRGBA const& color))0x51F970)(posn, color);
}

void CSprite2d::Draw(CRect const& posn, CRGBA const& color) {
	SetVertices(posn, color, color, color, color, 0);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, m_pTexture ? m_pTexture->raster : nullptr);
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
}

void CSprite2d::Draw(float x, float y, float w, float h, CRGBA const& color) {
	SetVertices(CRect(x, y + h, x + w, y), color, color, color, color, 0);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, m_pTexture ? m_pTexture->raster : nullptr);
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
}

void CSprite2d::Draw(CRect const& posn, CRGBA const& color, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4) {
	SetVertices(posn, color, color, color, color, u1, v1, u2, v2, u3, v3, u4, v4);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, m_pTexture ? m_pTexture->raster : nullptr);
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, maVertices, 4);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
}

void CSprite2d::SetVertices(CRect const& posn, CRGBA const& color1, CRGBA const& color2, CRGBA const& color3, CRGBA const& color4, unsigned int numVerts) {
	((void(__cdecl *)(CRect const&, CRGBA const&, CRGBA const&, CRGBA const&, CRGBA const&, unsigned int))0x51EE90)(posn, color1, color2, color3, color4, numVerts);
}

void CSprite2d::SetVertices(CRect const& posn, CRGBA const& color1, CRGBA const& color2, CRGBA const& color3, CRGBA const& color4, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4) {
	((void(__cdecl *)(CRect const&, CRGBA const&, CRGBA const&, CRGBA const&, CRGBA const&, float, float, float, float, float, float, float, float))0x51F220)(posn, color1, color2, color3, color4, u1, v1, u2, v2, u3, v3, u4, v4);
}

int CSprite2d::GetBank(int arg0, RwTexture* texture) {
	return ((int(__cdecl *)(int, RwTexture*))0x51EB70)(arg0, texture);
}

void CSprite2d::DrawBank(int arg0) {
	((void(__cdecl *)(int))0x51EC50)(arg0);
}
