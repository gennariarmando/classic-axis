#pragma once

#include "CVector.h"
#include "RenderWare.h"

struct IFrame {
	RtQuat m_qOrientation;
	CVector m_vecTranslation;
};

VALIDATE_SIZE(IFrame, 0x1C);

struct AnimBlendFrameData {
	unsigned char m_nFlags;
private:
	char _pad1[3];
public:
	CVector m_vecOffset;
	RwFrame *m_pIFrame;
	unsigned int m_nNodeId;
};

VALIDATE_SIZE(AnimBlendFrameData, 0x18);
