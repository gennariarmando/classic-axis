#pragma once
#include "CCam.h"

enum {
	TYPE_WALKAROUND,
	TYPE_STRAFE,
};

class CCamNew : public CCam {
public:
	CVector targetCoords;

public:
	void Process_FollowPed(CVector const& target, float targetOrient, float, float);
	void GetVectorsReadyForRW();
};
