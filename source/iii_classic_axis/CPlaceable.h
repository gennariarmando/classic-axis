#pragma once
#include "CMatrix.h"

class CPlaceable {
public:
	CMatrix m_matrix;
	//CPlaceable() : m_matrix() {}
	CPlaceable();
	bool IsWithinArea(float x1, float y1, float z1, float x2, float y2, float z2);
	bool IsWithinArea(float x1, float y1, float x2, float y2);
	void SetHeading(float heading);

	inline float GetHeading() {
		float angle = atan2f(-m_matrix.up.x, m_matrix.up.y);
		while (angle >= PI) angle = PI;
		while (angle < -PI) angle = -PI;
		return angle;
	}

	inline void SetPosition(float x, float y, float z) {
		this->m_matrix.pos.x = x;
		this->m_matrix.pos.y = y;
		this->m_matrix.pos.z = z;
	}

	inline void SetPosition(CVector &pos) {
		this->m_matrix.pos = pos;
	}

	inline void SetOrientation(float x, float y, float z) {
		CVector pos = this->m_matrix.pos;
		this->m_matrix.SetRotate(x, y, z);
		this->m_matrix.pos = pos;
	}

	inline void GetOrientation(float& x, float& y, float& z) {

		x = sin(this->m_matrix.up.z);

		float cosx = cosf(x);
		float cosy = this->m_matrix.at.z / cosx;
		y = cos(cosy);
		float cosz = this->m_matrix.up.y / cosx;
		z = cos(cosz);

	}

	virtual ~CPlaceable();
};

VALIDATE_SIZE(CPlaceable, 0x4C);