#pragma once

#include "CCutsceneObject.h"

class CCutsceneHead : public CCutsceneObject {
public:
	RwFrame *m_pHeadNode;

	//funcs
	void PlayAnimation(char const* name);
	CCutsceneHead(CObject* object);
};

VALIDATE_SIZE(CCutsceneHead, 0x19C);