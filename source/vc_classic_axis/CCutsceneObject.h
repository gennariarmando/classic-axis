#pragma once

#include "CObject.h"
#include "CCutsceneShadow.h"

class CCutsceneObject : public CObject {
public:
	CCutsceneShadow *m_pCutsceneShadow;
	RwFrame *m_pAttachTo;
	CObject *m_pAttachmentObject;

	CCutsceneObject();
};

VALIDATE_SIZE(CCutsceneObject, 0x1A0);