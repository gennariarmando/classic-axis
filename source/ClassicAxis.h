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

public:
    ClassicAxis();
    bool IsAbleToAim(CPed* ped);
    bool IsWeaponPossiblyCompatible(CPed* ped);
    bool IsTypeMelee(CPed* ped);
    bool IsTypeTwoHanded(CPed* ped);
    void DrawCrosshair();
    void DrawAutoAimTarget();
    void ClearWeaponTarget(CPlayerPed* ped);
};

extern ClassicAxis classicAxis;
