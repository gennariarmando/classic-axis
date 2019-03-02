#pragma once

#include "CVector.h"

class CRect {
public:
	float left;
	float bottom;
	float right;
	float top;

	inline CRect() {}

	inline CRect(float Left, float Bottom, float Right, float Top) {
		left = Left; bottom = Bottom; right = Right; top = Top;
	}
};

VALIDATE_SIZE(CRect, 0x10);