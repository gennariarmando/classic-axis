#pragma once
#define GINPUT_COMPILE_CROSSCOMPATIBLE_VERSION
#include "GInputAPI.h"

#include "Settings.h"

class ClassicAxis {
public:
    class IGInputPad* pXboxPad;
    bool isAiming;
    bool wasPointing;
    bool wasCrouching;
    bool ignoreRotation;
    bool forceRealMoveAnim;
    Settings settings;
    RwV3d lastLockOnPos;
    int timeLockOn;
    CRGBA lastLockOnColor;

public:
    ClassicAxis();
    void RotatePlayer(CPed* ped, float angle, bool smooth);
    bool IsAbleToAim(CPed* ped);
    bool IsType1stPerson(CPed* ped);
    bool IsWeaponPossiblyCompatible(CPed* ped);
    bool IsTypeMelee(CPed* ped);
    bool IsTypeTwoHanded(CPed* ped);
    void DrawCrosshair();
    void DrawAutoAimTarget();
    void ClearWeaponTarget(CPlayerPed* ped);
    void ProcessPlayerPedControl(CPed* ped);
    float Find3rdPersonQuickAimPitch(float y);
};

extern ClassicAxis classicAxis;
