#pragma once
#include "CCam.h"

enum {
    TYPE_WALKAROUND,
    TYPE_STRAFE,
};

enum {
#ifdef GTA3
    LAST_CAM_MODE = MODE_HELI_CANNON_1ST_PERSON,
#else
    LAST_CAM_MODE = MODE_CAMERA,
#endif
    MODE_PLACEHOLDER = LAST_CAM_MODE,
    MODE_AIMWEAPON,
};

class CCamNew {
public:
    CCam* cam;
    CVector targetCoords;
    bool cameraInput;
    std::vector<CEntity*> vecEntities;
    float previousPedZoomIndicator;
    float fovLerp;
    bool doFovChanges;
    float duckOffset;

public:
    CCamNew();
    ~CCamNew();
    void Process_FollowPed(CVector const&, float targetOrient, float, float);
    void Process_AimWeapon(CVector const&, float targetOrient, float, float);
    void Process_AvoidCollisions(float length);
    void Process_CrouchOffset(float &offset);
    void GetVectorsReadyForRW();
    void Process_FOVLerp();
};


extern const float minFOV;
extern const float maxFOV;
extern std::unique_ptr<CCamNew> CamNew;
