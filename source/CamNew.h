#pragma once
#include "CCam.h"

enum {
    TYPE_WALKAROUND,
    TYPE_STRAFE,
};

class CCamNew {
public:
    CCam* cam;
    CVector targetCoords;
    float lengthBeforeAiming;
    bool cameraInput;
    std::vector<CEntity*> vecEntities;
    float previousPedZoomIndicator;
    float previousPedZoomValue;
    float previoudPedZoomValueSmooth;
    float previousPedZoomValueScript;

public:
    CCamNew();
    ~CCamNew();
    void Process_FollowPed(CVector const&, float targetOrient, float, float);
    void Process_AimWeapon(CVector const&, float targetOrient, float, float);
    void Process_AvoidCollisions(float length);
    void GetVectorsReadyForRW();
};

extern std::shared_ptr<CCamNew> CamNew;
