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
    CPed* thirdPersonMouseTarget;
    float previousHorAngle;
    float previousVerAngle;
    bool camUseCurrentAngle;
    short previousCamMode;
    bool switchTransitionSpeed;

#ifdef GTA3
    bool weaponInfoSet;
    class CWeaponInfo weaponInfo[WEAPONTYPE_HELICANNON + 1];
#endif

public:
    ClassicAxis();
    void RotatePlayer(CPed* ped, float angle, bool smooth);
    void Clear();
    bool IsAbleToAim(CPed* ped);
    bool IsType1stPerson(CPed* ped);
    bool IsWeaponPossiblyCompatible(CPed* ped);
    bool IsTypeMelee(CPed* ped);
    bool IsTypeTwoHanded(CPed* ped);
    void DrawCrosshair();
    void DrawAutoAimTarget();
    void DrawTriangleForMouseRecruitPed();
    void ClearWeaponTarget(CPlayerPed* ped);
    void ProcessPlayerPedControl(CPlayerPed* ped);
    float Find3rdPersonQuickAimPitch(float y);
    void Find3rdPersonMouseTarget(CPlayerPed* ped);

#ifdef GTA3
    void SetDuck(CPlayerPed* ped);
    void ClearDuck(CPlayerPed* ped);
#endif
};

extern ClassicAxis classicAxis;
