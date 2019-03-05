#pragma once
#include "CMatrix.h"

class CPlaceable : public CMatrix {
public:
	//CPlaceable() : CMatrix() {}
	CPlaceable();
	bool IsWithinArea(float x1, float y1, float z1, float x2, float y2, float z2);
	bool IsWithinArea(float x1, float y1, float x2, float y2);
	void SetHeading(float heading);
	void SetOrientation(float x, float y, float z);
	void GetOrientation(float& x, float& y, float& z);

	inline float GetHeading() {
		float angle = atan2f(-up.x, up.y);
		while (angle >= PI) angle = PI;
		while (angle < -PI) angle = -PI;
		return angle;
	}
};