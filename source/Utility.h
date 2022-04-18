#pragma once
#include "CTimer.h"
#include "extensions/Screen.h"
#include "CSprite2d.h"

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

static void Draw2DPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, const CRGBA& color) {
	CSprite2d::SetVertices(x1, y1, x2, y2, x3, y3, x4, y4, color, color, color, color);
	RwRenderStateSet(rwRENDERSTATETEXTURERASTER, 0);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEFLAT);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)(color.a != 255));
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEGOURAUD);
}

static CVector2D RotateUV(CVector2D& uv, float rotation, CVector2D center) {
	CVector2D v = {
		cos(rotation) * (uv.x - center.x) + sin(rotation) * (uv.y - center.y) + center.x,
		cos(rotation) * (uv.y - center.y) - sin(rotation) * (uv.x - center.x) + center.y
	};

	uv = v;
	return v;
}

static void DrawTriangle(float x, float y, float scale, float angle, CRGBA const& col) {
	CVector2D posn[4];
	posn[0].x = 0.0f; posn[0].y = 0.0f; posn[1].x = 1.0f; posn[1].y = 0.0f;
	posn[2].x = 0.5f; posn[2].y = 1.0f; posn[3].x = 0.5f; posn[3].y = 1.0f;

	float w = scale * 0.8f;
	float h = scale;

	for (unsigned int i = 0; i < 4; i++) {
		posn[i].x *= w;
		posn[i].y *= h;

		posn[i].x += x;
		posn[i].y += y;
	}

	RotateUV(posn[0], angle, CVector2D(x + (w / 2), y + (h / 2)));
	RotateUV(posn[1], angle, CVector2D(x + (w / 2), y + (h / 2)));
	RotateUV(posn[2], angle, CVector2D(x + (w / 2), y + (h / 2)));
	RotateUV(posn[3], angle, CVector2D(x + (w / 2), y + (h / 2)));

	Draw2DPolygon(posn[0].x, posn[0].y, posn[1].x, posn[1].y, posn[2].x, posn[2].y, posn[3].x, posn[3].y, CRGBA(col));
}

static void DrawTarget(float x, float y, float dist, CRGBA const& col) {
	dist = clamp(dist, 0.2f, 1.0f);
	float offset = 28.0f * dist;

	x -= Scale(offset);
	DrawTriangle(x, y, Scale(14.0f), DegToRad(45.0f), CRGBA(0, 0, 0, 255));
	DrawTriangle(x, y, Scale(13.0f), DegToRad(45.0f), col);
	x += Scale(offset);

	x += Scale(offset);
	DrawTriangle(x, y, Scale(14.0f), DegToRad(-45.0f), CRGBA(0, 0, 0, 255));
	DrawTriangle(x, y, Scale(13.0f), DegToRad(-45.0f), col);
	x -= Scale(offset);

	y += Scale(offset * 1.5f);
	DrawTriangle(x, y, Scale(14.0f), DegToRad(180.0f), CRGBA(0, 0, 0, 255));
	DrawTriangle(x, y, Scale(13.0f), DegToRad(180.0f), col);
}
