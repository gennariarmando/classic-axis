#pragma once
#include "CTimer.h"
#include "extensions/Screen.h"
#include "CSprite2d.h"

#define defaultScreenWidth 640.0f
#define defaultScreenHeight 448.0f
#define defaultAspectRatio defaultScreenWidth / defaultScreenHeight
#define flashItem(on, off) (CTimer::m_snTimeInMillisecondsPauseMode % on + off < on)
#define interpF(a, b, f) a = a + (f) * (b - a)
#define clamp(v, low, high) ((v)<(low) ? (low) : (v)>(high) ? (high) : (v))
#define isNearlyEqualF(a, b, t) (fabs(a - b) <= t)
#define arraySize(array) (sizeof(array) / sizeof(array[0]))

static float DegToRad(float x) {
    return (x * M_PI / 180.0f);
}

static float RadToDeg(float x) {
    return (x * 180.0f / M_PI);
}

static float GetAspectRatio() {
#ifdef GTA3
    float& fScreenAspectRatio = *(float*)0x5F53C0;
#else
    float& fScreenAspectRatio = *(float*)0x94DD38;
#endif
    return fScreenAspectRatio;
}

static float ScaleX(float a) {
    return static_cast<float>(a * SCREEN_WIDTH / defaultScreenWidth) * defaultAspectRatio / GetAspectRatio();
}

static float ScaleY(float a) {
    return static_cast<float>(a * SCREEN_HEIGHT / defaultScreenHeight);
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

static void RotateVertices(CVector2D* rect, float x, float y, float angle) {
    float xold, yold;
    //angle /= 57.2957795;
    float _cos = cosf(angle);
    float _sin = sinf(angle);
    for (unsigned int i = 0; i < 4; i++) {
        xold = rect[i].x;
        yold = rect[i].y;
        rect[i].x = x + (xold - x) * _cos + (yold - y) * _sin;
        rect[i].y = y - (xold - x) * _sin + (yold - y) * _cos;
    }
}

static void DrawTriangle(float x, float y, float w, float h, CVector2D center, float angle, CRGBA const& col) {
    CVector2D posn[4];
    posn[1].x = x - (w * 0.5f); posn[1].y = y - (h * 0.5f); posn[0].x = x + (w * 0.5f); posn[0].y = y - (h * 0.5f);
    posn[3].x = x; posn[3].y = y + (h * 0.5f);	posn[2].x = x; posn[2].y = y + (h * 0.5f);

    RotateVertices(posn, x + (w * center.x), y + (h * center.y), angle);
    Draw2DPolygon(posn[0].x, posn[0].y, posn[1].x, posn[1].y, posn[2].x, posn[2].y, posn[3].x, posn[3].y, CRGBA(col));
}

static void DrawLCSTarget(float x, float y, float dist, CRGBA const& col) {
    dist = clamp(dist, 0.1f, 1.0f);
    float offset = 32.0f * dist;

    x += ScaleY(-offset);
    DrawTriangle(x, y, ScaleY(9.0f * 0.6f), ScaleY(9.0f), CVector2D(0.0f, 0.0f), DegToRad(55.0f), CRGBA(0, 0, 0, col.a));
    DrawTriangle(x, y, ScaleY(8.0f * 0.6f), ScaleY(8.0f), CVector2D(0.0f, 0.0f), DegToRad(55.0f), col);
    x += ScaleY(offset);

    x += ScaleY(offset);
    DrawTriangle(x, y, ScaleY(9.0f * 0.6f), ScaleY(9.0f), CVector2D(0.0f, 0.0f),DegToRad(-55.0f), CRGBA(0, 0, 0, col.a));
    DrawTriangle(x, y, ScaleY(8.0f * 0.6f), ScaleY(8.0f), CVector2D(0.0f, 0.0f),DegToRad(-55.0f), col);
    x += ScaleY(-offset);

    y += ScaleY(offset * 1.5f);
    DrawTriangle(x, y, ScaleY(9.0f * 0.6f), ScaleY(9.0f), CVector2D(0.0f, 0.0f),DegToRad(180.0f), CRGBA(0, 0, 0, col.a));
    DrawTriangle(x, y, ScaleY(8.0f * 0.6f), ScaleY(8.0f), CVector2D(0.0f, 0.0f),DegToRad(180.0f), col);
}

static void DrawSATarget(float x, float y, float dist, float rotationMult, CRGBA const& col) {
    dist = clamp(dist, 0.6f, 1.0f);

    static float angle = 0.0f;
    angle += ((0.2f * rotationMult) * CTimer::ms_fTimeStep);

    float b = ScaleY(10.0f * dist);
    float s = ScaleY(9.8f * dist);
    DrawTriangle(x, y, b * 0.8f, b, CVector2D(0.0f, dist + 1.0f), DegToRad(60.0f) - angle, CRGBA(0, 0, 0, col.a));
    DrawTriangle(x, y, s * 0.8f, s, CVector2D(0.0f, dist + 1.0f), DegToRad(60.0f) - angle, col);
    DrawTriangle(x, y, b * 0.8f, b, CVector2D(0.0f, dist + 1.0f), DegToRad(-60.0f) - angle, CRGBA(0, 0, 0, col.a));
    DrawTriangle(x, y, s * 0.8f, s, CVector2D(0.0f, dist + 1.0f), DegToRad(-60.0f) - angle, col);
    DrawTriangle(x, y, b * 0.8f, b, CVector2D(0.0f, dist + 1.0f), DegToRad(180.0f) - angle, CRGBA(0, 0, 0, col.a));
    DrawTriangle(x, y, s * 0.8f, s, CVector2D(0.0f, dist + 1.0f), DegToRad(180.0f) - angle, col);
}

static void DrawSATriangleForMouseRecruit(float x, float y, float dist, CRGBA const& col) {
    dist = clamp(dist, 0.0f, 1.0f);

    DrawTriangle(x, y, ScaleY(20.0f * dist), ScaleY(10.0f * dist), CVector2D(0.0f, 0.0f), DegToRad(180.0f), col);
}
