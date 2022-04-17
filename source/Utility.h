#pragma once
#include "CTimer.h"
#include "extensions/Screen.h"

#define interpF(a, b, f) a = a + (f) * (b - a)
#define clamp(v, low, high) ((v)<(low) ? (low) : (v)>(high) ? (high) : (v))

static float DegToRad(float x) {
	return (x * M_PI / 180.0f);
}

static float RadToDeg(float x) {
	return (x * 180.0f / M_PI);
}

static float GetAspectRatio() {
	float& fScreenAspectRatio = *(float*)0x5F53C0;
	return fScreenAspectRatio;
}

static float Scale(float a) {
	return static_cast<int>(a * GetAspectRatio());
}

static float DotProduct(const CVector& v1, const CVector& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

static CVector CrossProduct(const CVector& v1, const CVector& v2) {
	return CVector(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

static float Magnitude2d(CVector v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

static void WellBufferMe(float Target, float* CurrentValue, float* CurrentSpeed, float MaxSpeed, float Acceleration, bool IsAngle) {
	float Delta = Target - *CurrentValue;

	if (IsAngle) {
		while (Delta >= M_PI) Delta -= 2 * M_PI;
		while (Delta < -M_PI) Delta += 2 * M_PI;
	}

	float TargetSpeed = Delta * MaxSpeed;
	*CurrentSpeed += Acceleration * (TargetSpeed - *CurrentSpeed) * CTimer::ms_fTimeStep;

	if (TargetSpeed < 0.0f && *CurrentSpeed < TargetSpeed)
		*CurrentSpeed = TargetSpeed;
	else if (TargetSpeed > 0.0f && *CurrentSpeed > TargetSpeed)
		*CurrentSpeed = TargetSpeed;

	*CurrentValue += *CurrentSpeed * min(10.0f, CTimer::ms_fTimeStep);
}

static CVector TransformFromObjectSpace(CMatrix const& m, float heading, CVector const& offset) {
	RwMatrix* p = m.m_pAttachMatrix;
	if (p) {
		CVector point = operator*(m, offset);
		return point;
	}
	return CVector();
}
