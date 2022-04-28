#pragma once
#include "CCam.h"

enum {
    TYPE_WALKAROUND,
    TYPE_STRAFE,
};

enum {
#ifdef GTA3
    LAST_CAM_MODE = 43,
#else
    LAST_CAM_MODE = 46,
#endif
    MODE_AIMWEAPON = 47,
};

class CCamNew {
public:
    CCam* cam;
    CVector targetCoords;
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
