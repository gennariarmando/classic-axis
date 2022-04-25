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
    bool wasAiming;
    bool cameraInput;

public:
    CCamNew();
    ~CCamNew();
    void Process_FollowPed(CVector const& target, float targetOrient, float, float);
    void GetVectorsReadyForRW();
};

extern std::shared_ptr<CCamNew> CamNew;
