#pragma once

#include "RenderWare.h"
#include <math.h>

class CVector {
public:
	float x, y, z;

	inline CVector() {}

	inline CVector(float X, float Y, float Z) {
		x = X; y = Y; z = Z;
	}

	inline CVector(CVector const& src) {
		x = src.x; y = src.y; z = src.z;
	}

	inline void Cross(CVector &a, CVector &b) {
		this->x = b.z * a.y - a.z * b.y;
		this->y = a.z * b.x - a.x * b.z;
		this->z = a.x * b.y - b.x * a.y;
	}

	inline float Magnitude() {
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	inline float Magnitude2d() {
		return sqrt(this->x * this->x + this->y * this->y);
	}

	inline void Sum(CVector &a, CVector &b) {
		this->x = a.x + b.x;
		this->y = a.y + b.y;
		this->z = a.z + b.z;
	}

	inline void Difference(CVector &a, CVector &b) {
		this->x = a.x - b.x;
		this->y = a.y - b.y;
		this->z = a.z - b.z;
	}

	inline void operator=(const CVector& right) {
		this->x = right.x;
		this->y = right.y;
		this->z = right.z;
	}

	inline void operator+=(const CVector& right) {
		this->x += right.x;
		this->y += right.y;
		this->z += right.z;
	}

	inline void operator-=(const CVector& right) {
		this->x -= right.x;
		this->y -= right.y;
		this->z -= right.z;
	}

	inline void operator *= (float multiplier) {
		this->x *= multiplier;
		this->y *= multiplier;
		this->z *= multiplier;
	}

	inline void operator /= (float divisor) {
		this->x /= divisor;
		this->y /= divisor;
		this->z /= divisor;
	}

	float Normalise();

	inline RwV3d ToRwV3d() const {
		return{ x, y, z };
	}

	inline void FromRwV3d(RwV3d &rwvec) {
		x = rwvec.x; y = rwvec.y; z = rwvec.z;
	}

	inline void Set(float X, float Y, float Z) {
		x = X; y = Y; z = Z;
	}
};

inline float operator-(const CVector& vecOne, const float& value) {
	return (vecOne.x - value, vecOne.y - value, vecOne.z - value);
}

inline float operator-(const float& value, const CVector& vecTwo) {
	return (value - vecTwo.x, value - vecTwo.y, value - vecTwo.z);
}

inline CVector operator-(const CVector& vecOne, const CVector& vecTwo) {
	return CVector(vecOne.x - vecTwo.x, vecOne.y - vecTwo.y, vecOne.z - vecTwo.z);
}

inline CVector operator+(const CVector& vecOne, const CVector& vecTwo) {
	return CVector(vecOne.x + vecTwo.x, vecOne.y + vecTwo.y, vecOne.z + vecTwo.z);
}

inline CVector operator*(const CVector& vec, const CVector& vecTwo) {
	return CVector(vec.x * vecTwo.x, vec.y * vecTwo.y, vec.z * vecTwo.z);
}

inline CVector operator*(const CVector& vec, float multiplier) {
	return CVector(vec.x * multiplier, vec.y * multiplier, vec.z * multiplier);
}

inline CVector operator/(const CVector& vec, float multiplier) {
	return CVector(vec.x / multiplier, vec.y / multiplier, vec.z / multiplier);
}

inline CVector operator*(float multiplier, const CVector& vec) {
	return CVector(vec.x * multiplier, vec.y * multiplier, vec.z * multiplier);
}

inline CVector operator+=(const CVector& vec, const RwV3d& vec2) {
	return CVector(vec.x + vec2.x, vec.y + vec2.y, vec.z + vec2.z);
}

inline float DistanceBetweenPoints(const CVector &pointOne, const CVector &pointTwo) {
	CVector diff = pointTwo - pointOne;
	return diff.Magnitude();
}

class CVector2D {
public:
	float x, y;

	inline CVector2D() {
		x = 0.0f; y = 0.0f;
	}

	inline CVector2D(float X, float Y) {
		x = X; y = Y;
	}

	inline CVector2D(CVector2D const& src) {
		x = src.x; y = src.y;
	}

	inline float Magnitude() {
		return sqrtf(this->x * this->x + this->y * this->y);
	}

	inline void Sum(CVector2D &a, CVector2D &b) {
		this->x = a.x + b.x;
		this->y = a.y + b.y;
	}

	inline void Difference(CVector2D &a, CVector2D &b) {
		this->x = a.x - b.x;
		this->y = a.y - b.y;
	}

	inline void operator=(const CVector2D& right) {
		this->x = right.x;
		this->y = right.y;
	}

	inline void operator+=(const CVector2D& right) {
		this->x += right.x;
		this->y += right.y;
	}

	inline void operator-=(const CVector2D& right) {
		this->x -= right.x;
		this->y -= right.y;
	}

	inline void operator *= (float multiplier) {
		this->x *= multiplier;
		this->y *= multiplier;
	}

	inline void operator /= (float divisor) {
		this->x /= divisor;
		this->y /= divisor;
	}
};

static inline CVector CrossProduct(const CVector &v1, const CVector &v2) {
	return CVector(v1.y*v2.z - v1.z*v2.y,
		v1.z*v2.x - v1.x*v2.z,
		v1.x*v2.y - v1.y*v2.x);
}

static inline float DotProduct(const CVector &v1, const CVector &v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}