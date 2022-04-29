#include "plugin.h"
#include "CCam.h"
#include "CCamera.h"
#include "CGeneral.h"
#include "CTimer.h"
#include "CWorld.h"
#include "CScene.h"
#include "CDraw.h"
#include "CFont.h"
#include "CWeaponInfo.h"

#include "ClassicAxis.h"
#include "CamNew.h"
#include "Utility.h"

using namespace plugin;

#ifdef GTA3
CColPoint* gaTempSphereColPoints = (CColPoint*)0x6E64C0;
#else
CColPoint* gaTempSphereColPoints = (CColPoint*)0x7D18C0;
#endif
std::shared_ptr<CCamNew> CamNew;

CCamNew::CCamNew() {
    cam = &TheCamera.m_asCams[TheCamera.m_nActiveCam];
    targetCoords = {};
    cameraInput = false;
    vecEntities.resize(5);
    previousPedZoomIndicator = 0.0f;
}

CCamNew::~CCamNew() {
    cam = NULL;
}

void CCamNew::Process_FollowPed(CVector const& target, float targetOrient, float, float) {
    if (!cam)
        return;

    CPed* e = static_cast<CPed*>(cam->m_pCamTargetEntity);

    if (e->m_nType != ENTITY_TYPE_PED)
        return;

    cam->m_fFOV = 70.0f;

    const float minDist = 2.0f;
#ifdef GTA3
    const float maxDist = minDist + TheCamera.m_fPedZoomValueSmooth;
#else
    const float maxDist = minDist + TheCamera.m_fPedZoomValueScript;
#endif
    const float heightOffset = 0.5f;
    const bool usingController = classicAxis.pXboxPad->HasPadInHands();

    targetCoords = target;
    targetCoords.z += cam->m_fSyphonModeTargetZOffSet;
    targetCoords.z += heightOffset;

    CVector dist = cam->m_vecSource - targetCoords;

    if (cam->m_bResetStatics) {
        cam->m_fHorizontalAngle = CGeneral::GetATanOfXY(-dist.x, -dist.y);
        cam->m_fVerticalAngle = 0.0f;

        dist = maxDist * CVector(cosf(cam->m_fVerticalAngle) * cosf(cam->m_fHorizontalAngle), cosf(cam->m_fVerticalAngle) * sinf(cam->m_fHorizontalAngle), sinf(cam->m_fVerticalAngle));
        cam->m_vecSource = targetCoords + dist;

        cam->m_bResetStatics = false;
    }

    float length = dist.Magnitude();

    if (previousPedZoomIndicator != maxDist) {
        dist *= maxDist / length;
        previousPedZoomIndicator = maxDist;
    }
    else {
        if (length == 0.0f)
            dist = CVector(1.0f, 1.0f, 0.0f);
        else if (length < minDist)
            dist *= minDist / length;
        else if (length > maxDist)
            dist *= maxDist / length;
    }

    length = dist.Magnitude();

    bool lockMovement = false;
    if (usingController && TheCamera.m_nTransitionState == 0) {
        cam->m_fHorizontalAngle = CGeneral::GetATanOfXY(-dist.x, -dist.y);
        cam->m_fVerticalAngle = CGeneral::GetATanOfXY(Magnitude2d(dist), -dist.z);
    }
    while (cam->m_fHorizontalAngle >= M_PI) cam->m_fHorizontalAngle -= 2.0f * M_PI;
    while (cam->m_fHorizontalAngle < -M_PI) cam->m_fHorizontalAngle += 2.0f * M_PI;
    while (cam->m_fVerticalAngle >= M_PI) cam->m_fVerticalAngle -= 2.0f * M_PI;
    while (cam->m_fVerticalAngle < -M_PI) cam->m_fVerticalAngle += 2.0f * M_PI;

    CPad* pad = CPad::GetPad(0);
    if (pad->DisablePlayerControls)
        lockMovement = true;
    float lookLeftRight = -pad->LookAroundLeftRight();
    float lookUpDown = pad->LookAroundUpDown();
    float mouseX = pad->NewMouseControllerState.X;
    float mouseY = pad->NewMouseControllerState.Y;
    bool mouseInput = false;

    if (mouseX != 0.0f || mouseY != 0.0f) {
        mouseInput = true;
        lookLeftRight = -2.5f * mouseX;
        lookUpDown = 4.0f * mouseY;
    }

    float betaOffset = lookLeftRight * 0.01f * (1.0f / 20.0f) * cam->m_fFOV / 80.0f * CTimer::ms_fTimeStep;
    float alphaOffset = lookUpDown * 0.01f * (0.6f / 20.0f) * cam->m_fFOV / 80.0f * CTimer::ms_fTimeStep;

    if (mouseInput) {
        betaOffset = lookLeftRight * TheCamera.m_fMouseAccelHorzntal * cam->m_fFOV / 80.0f;
        alphaOffset = lookUpDown * TheCamera.m_fMouseAccelHorzntal * cam->m_fFOV / 80.0f;
    }

    if (betaOffset || alphaOffset || lockMovement) {
        cam->m_bRotating = false;
        cameraInput = true;
    }
    else
        cameraInput = false;

    if (!lockMovement) {
        cam->m_fHorizontalAngle += betaOffset;
        cam->m_fVerticalAngle += alphaOffset;
    }

    while (cam->m_fHorizontalAngle >= M_PI) cam->m_fHorizontalAngle -= 2.0f * M_PI;
    while (cam->m_fHorizontalAngle < -M_PI) cam->m_fHorizontalAngle += 2.0f * M_PI;

    if (cam->m_fVerticalAngle > DegToRad(60.0f))
        cam->m_fVerticalAngle = DegToRad(60.0f);
    else if (cam->m_fVerticalAngle < -DegToRad(89.5f))
        cam->m_fVerticalAngle = -DegToRad(89.5f);

    if (CPad::GetPad(0)->ForceCameraBehindPlayer() && !lockMovement) {
        cam->m_fTargetBeta = targetOrient;
        cam->m_bRotating = true;
    }

    if (cam->m_bRotating) {
        WellBufferMe(cam->m_fTargetBeta, &cam->m_fHorizontalAngle, &cam->m_fBetaSpeed, 0.1f, 0.06f, true);
        float DeltaBeta = cam->m_fTargetBeta - cam->m_fHorizontalAngle;
        while (DeltaBeta >= M_PI) DeltaBeta -= 2 * M_PI;
        while (DeltaBeta < -M_PI) DeltaBeta += 2 * M_PI;
        if (abs(DeltaBeta) < 0.06f)
            cam->m_bRotating = false;
    }

    if (TheCamera.m_bUseTransitionBeta)
        cam->m_fHorizontalAngle = CGeneral::GetATanOfXY(-cos(cam->m_fTransitionBeta), -sin(cam->m_fTransitionBeta));

    if (TheCamera.m_bCamDirectlyBehind) {
        cam->m_bCollisionChecksOn = 1;
        cam->m_fHorizontalAngle = targetOrient;
        cam->m_fVerticalAngle = 0.0f;
        TheCamera.m_bCamDirectlyBehind = false;
    }

    if (TheCamera.m_bCamDirectlyInFront) {
        cam->m_fHorizontalAngle = targetOrient + M_PI;
        cam->m_fVerticalAngle = 0.0f;
        TheCamera.m_bCamDirectlyInFront = false;
    }

    if (classicAxis.camUseCurrentAngle) {
        cam->m_fHorizontalAngle = classicAxis.previousHorAngle;
        cam->m_fVerticalAngle = classicAxis.previousVerAngle;
        classicAxis.camUseCurrentAngle = false;
    }

    cam->m_fDistanceBeforeChanges = (cam->m_vecSource - targetCoords).Magnitude();

    cam->m_vecFront = CVector(cos(cam->m_fVerticalAngle) * cos(cam->m_fHorizontalAngle), cos(cam->m_fVerticalAngle) * sin(cam->m_fHorizontalAngle), sin(cam->m_fVerticalAngle));
    cam->m_vecSource = targetCoords - cam->m_vecFront * length;
    cam->m_vecSourceBeforeLookBehind = targetCoords + cam->m_vecFront;
    targetCoords.z -= heightOffset;

    cam->m_vecTargetCoorsForFudgeInter = targetCoords;

    cam->m_vecFront = targetCoords - cam->m_vecSource;
    cam->m_vecFront.Normalise();

    Process_AvoidCollisions(length);
    GetVectorsReadyForRW();
}

void CCamNew::Process_AimWeapon(CVector const& target, float targetOrient, float, float) {
    if (!cam)
        return;

    if (cam->m_pCamTargetEntity->m_nType != ENTITY_TYPE_PED)
        return;

    CPlayerPed* e = static_cast<CPlayerPed*>(cam->m_pCamTargetEntity);

    cam->m_fFOV = 70.0f;

    const float maxDist = 2.7f;
    const float heightOffset = 0.25f;

    CVector aimOffset = CVector(0.52f, 0.0f, 0.55f);

    float length = maxDist;
    if (!classicAxis.settings.lcsAimingCoords) {
        aimOffset = CVector(0.25f, 0.0f, 0.5f);

        const eWeaponType weaponType = e->m_aWeapons[e->m_nCurrentWeapon].m_eWeaponType;
        CWeaponInfo* info = CWeaponInfo::GetWeaponInfo(weaponType);

        if (!info->m_bCanAimWithArm && info->m_bCanAim) {
            length -= 0.5f;
            aimOffset.z += 0.025f;
        }
    }

#ifdef GTA3
    CMatrix& mat = e->m_matrix;
#else
    CMatrix& mat = e->m_placement;
#endif
    targetCoords = TransformFromObjectSpace(mat, e->GetHeading(), aimOffset);

    CEntity* entity = NULL;
    CColPoint colPoint;

    if (CWorld::ProcessLineOfSight(targetCoords, cam->m_vecSource, colPoint, entity, true, false, false, true, false, true, true
#ifndef GTA3
        , false
#endif
    )) {
        targetCoords = target;
    }

    targetCoords.z += heightOffset;

    CVector dist = cam->m_vecSource - targetCoords;

    bool lockMovement = false;
    CEntity* p = e->m_pPointGunAt;
    if (e->m_bHasLockOnTarget && !cam->m_bLookingBehind && p) {
        CVector target = p->GetPosition();
        CVector distfromTarget = (cam->m_vecSource - target);
        CVector distFromCamEntity = (e->GetPosition() - target);
        float viewPlaneHeight = tan(DegToRad(cam->m_fFOV) * 0.5f);
        float viewPlaneWidth = viewPlaneHeight * GetAspectRatio() * 1.05f;

        float horShift = CGeneral::GetATanOfXY(1.0f, (TheCamera.m_f3rdPersonCHairMultX - 0.5f + TheCamera.m_f3rdPersonCHairMultX - 0.5f) * viewPlaneWidth);
        float verShift = CGeneral::GetATanOfXY(1.0f, (viewPlaneHeight * 0.0174f) * ((0.5f - TheCamera.m_f3rdPersonCHairMultY + 0.5f - TheCamera.m_f3rdPersonCHairMultY) * (1.0f / GetAspectRatio())));
        cam->m_fHorizontalAngle = e->m_fRotationCur + (M_PI * 0.5f) + horShift;
        cam->m_fVerticalAngle = CGeneral::GetATanOfXY(Magnitude2d(distfromTarget), -distfromTarget.z) - verShift;

        lockMovement = true;
    }

    while (cam->m_fHorizontalAngle >= M_PI) cam->m_fHorizontalAngle -= 2.0f * M_PI;
    while (cam->m_fHorizontalAngle < -M_PI) cam->m_fHorizontalAngle += 2.0f * M_PI;
    while (cam->m_fVerticalAngle >= M_PI) cam->m_fVerticalAngle -= 2.0f * M_PI;
    while (cam->m_fVerticalAngle < -M_PI) cam->m_fVerticalAngle += 2.0f * M_PI;

    CPad* pad = CPad::GetPad(0);
    if (pad->DisablePlayerControls)
        lockMovement = true;
    float lookLeftRight = -pad->LookAroundLeftRight();
    float lookUpDown = pad->LookAroundUpDown();
    float mouseX = pad->NewMouseControllerState.X;
    float mouseY = pad->NewMouseControllerState.Y;
    bool mouseInput = false;

    if (mouseX != 0.0f || mouseY != 0.0f) {
        mouseInput = true;
        lookLeftRight = -2.5f * mouseX;
        lookUpDown = 4.0f * mouseY;
    }

    float betaOffset = lookLeftRight * 0.01f * (1.0f / 20.0f) * cam->m_fFOV / 80.0f * CTimer::ms_fTimeStep;
    float alphaOffset = lookUpDown * 0.01f * (0.6f / 20.0f) * cam->m_fFOV / 80.0f * CTimer::ms_fTimeStep;

    if (mouseInput) {
        betaOffset = lookLeftRight * TheCamera.m_fMouseAccelHorzntal * cam->m_fFOV / 80.0f;
        alphaOffset = lookUpDown * TheCamera.m_fMouseAccelHorzntal * cam->m_fFOV / 80.0f;
    }

    if (betaOffset || alphaOffset || lockMovement) {
        cam->m_bRotating = false;
        cameraInput = true;
    }
    else
        cameraInput = false;

    if (!lockMovement) {
        cam->m_fHorizontalAngle += betaOffset;
        cam->m_fVerticalAngle += alphaOffset;
    }

    while (cam->m_fHorizontalAngle >= M_PI) cam->m_fHorizontalAngle -= 2.0f * M_PI;
    while (cam->m_fHorizontalAngle < -M_PI) cam->m_fHorizontalAngle += 2.0f * M_PI;

    if (cam->m_fVerticalAngle > DegToRad(45.0f))
        cam->m_fVerticalAngle = DegToRad(45.0f);
    else if (cam->m_fVerticalAngle < -DegToRad(45.0f))
        cam->m_fVerticalAngle = -DegToRad(45.0f);

    if (TheCamera.m_bCamDirectlyBehind) {
        cam->m_bCollisionChecksOn = 1;
        cam->m_fHorizontalAngle = targetOrient;
        cam->m_fVerticalAngle = 0.0f;
        TheCamera.m_bCamDirectlyBehind = false;
    }

    if (TheCamera.m_bCamDirectlyInFront) {
        cam->m_fHorizontalAngle = targetOrient + M_PI;
        cam->m_fVerticalAngle = 0.0f;
        TheCamera.m_bCamDirectlyInFront = false;
    }

    if (classicAxis.camUseCurrentAngle) {
        cam->m_fHorizontalAngle = classicAxis.previousHorAngle;
        cam->m_fVerticalAngle = classicAxis.previousVerAngle;
        classicAxis.camUseCurrentAngle = false;
    }

    cam->m_fDistanceBeforeChanges = (cam->m_vecSource - targetCoords).Magnitude();
    cam->m_vecFront = CVector(cos(cam->m_fVerticalAngle) * cos(cam->m_fHorizontalAngle), cos(cam->m_fVerticalAngle) * sin(cam->m_fHorizontalAngle), sin(cam->m_fVerticalAngle));
    cam->m_vecSource = targetCoords - cam->m_vecFront * length;
    cam->m_vecSourceBeforeLookBehind = targetCoords + cam->m_vecFront;
    targetCoords.z -= heightOffset;

    cam->m_vecTargetCoorsForFudgeInter = targetCoords;

    cam->m_vecFront = targetCoords - cam->m_vecSource;
    cam->m_vecFront.Normalise();

    Process_AvoidCollisions(length);

    GetVectorsReadyForRW();
}

void CCamNew::Process_AvoidCollisions(float length) {
    CColPoint colPoint = {};
    CEntity* entity = NULL;

    CWorld::pIgnoreEntity = cam->m_pCamTargetEntity;

    if (CWorld::ProcessLineOfSight(targetCoords, cam->m_vecSource, colPoint, entity, true, true, false, true, false, false, false
#ifdef GTAVC 
        , false
#endif
    )) {
        float distFromPoint = (targetCoords - colPoint.m_vecPoint).Magnitude();
        cam->m_vecSource = colPoint.m_vecPoint;
        if (distFromPoint < 1.3f)
            RwCameraSetNearClipPlane(Scene.m_pCamera, max(distFromPoint - 0.3f, 0.05f));
    }

    float viewPlaneHeight = tan(DegToRad(cam->m_fFOV) * 0.5f);
    float viewPlaneWidth = viewPlaneHeight * GetAspectRatio() * 1.05f;

    CWorld::pIgnoreEntity = NULL;
    for (int i = 0; i < 5; i++) {
        if (vecEntities[i]) {
            vecEntities[i]->m_nFlags.bIsVisible = true;
            vecEntities[i] = NULL;
        }

        float nearClip = RwCameraGetNearClipPlane(Scene.m_pCamera);
        float radius = (viewPlaneWidth * nearClip);
        CVector center = cam->m_vecSource + cam->m_vecFront * nearClip;
        if (entity = CWorld::TestSphereAgainstWorld(center, radius, NULL, true, true, true, true, false, true)) {
            bool isTypePed = entity->m_nType == ENTITY_TYPE_PED;

            if (isTypePed && entity->IsVisible() && Magnitude2d((center - entity->GetPosition())) < 0.5f) {
                if (TheCamera.m_nTransitionState == 0) {
                    vecEntities[i] = entity;
                    entity->m_nFlags.bIsVisible = false;
                }
            }
            else if (!isTypePed) {
                CVector distFromPoint = gaTempSphereColPoints[0].m_vecPoint - targetCoords;
                float frontDist = DotProduct(distFromPoint, cam->m_vecFront);
                float dist = (distFromPoint - cam->m_vecFront * frontDist).Magnitude() / viewPlaneWidth;

                dist = max(min(nearClip, dist), 0.1f);
                if (dist < nearClip)
                    RwCameraSetNearClipPlane(Scene.m_pCamera, dist);

                if (dist == 0.1f)
                    cam->m_vecSource += (targetCoords - cam->m_vecSource) * (dist / length);
            }
        }
    }
}

void CCamNew::GetVectorsReadyForRW() {
    if (!cam)
        return;

    CVector right;
    cam->m_vecUp = CVector(0.0f, 0.0f, 1.0f);
    cam->m_vecFront.Normalise();
    if (cam->m_vecFront.x == 0.0f && cam->m_vecFront.y == 0.0f) {
        cam->m_vecFront.x = 0.0001f;
        cam->m_vecFront.y = 0.0001f;
    }
    right = CrossProduct(cam->m_vecFront, cam->m_vecUp);
    right.Normalise();
    cam->m_vecUp = CrossProduct(right, cam->m_vecFront);
}
