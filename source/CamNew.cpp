#include "ClassicAxis.h"
#include "CamNew.h"
#include "Utility.h"

// plugin-sdk
#include "plugin.h"
#include "CCam.h"
#include "CCamera.h"
#include "CGeneral.h"
#include "CTimer.h"
#include "CWorld.h"
#include "CScene.h"
#include "CDraw.h"
#include "CFont.h"

using namespace plugin;

std::shared_ptr<CCamNew> CamNew;

CCamNew::CCamNew() {
    cam = NULL;
    targetCoords = {};
    lengthBeforeAiming = 0.0f;
    wasAiming = false;
    cameraInput = false;
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
    const bool aimingWeaponChanges = classicAxis.isAiming;
    const bool usingController = classicAxis.pXboxPad->HasPadInHands();

    RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);
    if (aimingWeaponChanges) {
        CVector aimOffset = CVector(0.5f, 0.0f, 0.5f);

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

        wasAiming = true;
    }
    else {
        targetCoords = target;
        targetCoords.z += cam->m_fSyphonModeTargetZOffSet;
    }

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
    if (aimingWeaponChanges) {
        length = minDist;
    }
    else {
        length = maxDist;

        if (wasAiming) {
            length = lengthBeforeAiming;
            wasAiming = false;
        }

        lengthBeforeAiming = length;
    }

    bool lockMovement = false;
    CEntity* p = e->m_pPointGunAt;
    if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget && !cam->m_bLookingBehind && p) {
        CVector target = p->GetPosition();
        CVector targetDiff = (cam->m_vecSource - target);

        cam->m_fHorizontalAngle = CGeneral::GetATanOfXY(targetDiff.x, targetDiff.y) + M_PI;
        cam->m_fVerticalAngle = CGeneral::GetATanOfXY(Magnitude2d(targetDiff), -targetDiff.z) + M_1_PI / 2;
        lockMovement = true;
    }
    else if (usingController && !aimingWeaponChanges && !cam->m_bLookingBehind && !cameraInput) {
        cam->m_fHorizontalAngle = CGeneral::GetATanOfXY(-dist.x, -dist.y);
        cam->m_fVerticalAngle = CGeneral::GetATanOfXY(Magnitude2d(dist), -dist.z);
    }

    while (cam->m_fHorizontalAngle >= M_PI) cam->m_fHorizontalAngle -= 2.0f * M_PI;
    while (cam->m_fHorizontalAngle < -M_PI) cam->m_fHorizontalAngle += 2.0f * M_PI;
    while (cam->m_fVerticalAngle >= M_PI) cam->m_fVerticalAngle -= 2.0f * M_PI;
    while (cam->m_fVerticalAngle < -M_PI) cam->m_fVerticalAngle += 2.0f * M_PI;

    float lookLeftRight = -CPad::GetPad(0)->LookAroundLeftRight();
    float lookUpDown = CPad::GetPad(0)->LookAroundUpDown();
    float mouseX = CPad::GetPad(0)->NewMouseControllerState.X;
    float mouseY = CPad::GetPad(0)->NewMouseControllerState.Y;
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
    else if (cam->m_fVerticalAngle < -DegToRad(89.5f))
        cam->m_fVerticalAngle = -DegToRad(89.5f);

    if (CPad::GetPad(0)->ForceCameraBehindPlayer() && !lockMovement) {
        cam->m_fTargetBeta = targetOrient;
        cam->m_bRotating = true;
    }

    if (aimingWeaponChanges)
        cam->m_bRotating = false;

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

    cam->m_fDistanceBeforeChanges = (cam->m_vecSource - targetCoords).Magnitude();

    cam->m_vecFront = CVector(cos(cam->m_fVerticalAngle) * cos(cam->m_fHorizontalAngle), cos(cam->m_fVerticalAngle) * sin(cam->m_fHorizontalAngle), sin(cam->m_fVerticalAngle));
    cam->m_vecSource = targetCoords - cam->m_vecFront * length;
    cam->m_vecSourceBeforeLookBehind = targetCoords + cam->m_vecFront;
    targetCoords.z -= heightOffset;

    cam->m_vecTargetCoorsForFudgeInter = targetCoords;

    cam->m_vecFront = targetCoords - cam->m_vecSource;
    cam->m_vecFront.Normalise();

    CEntity* entity = NULL;
    CColPoint colPoint;
    CWorld::pIgnoreEntity = e;

    if (CWorld::ProcessLineOfSight(targetCoords, cam->m_vecSource, colPoint, entity, true, true, false, true, false, true, true
#ifndef GTA3
        , false
#endif
    )) {
        cam->m_vecSource = colPoint.m_vecPoint;

        CVector d = cam->m_vecSource - targetCoords;
        float l = d.Magnitude();
        if (l > 0.4f) {
            d.x = d.x / l * (l - 0.3f);
            d.y = d.y / l * (l - 0.3f);
            d.z = d.z / l * (l - 0.3f);

        }
        cam->m_vecSource = targetCoords + d;

        if (Magnitude2d(targetCoords - cam->m_vecSource) < 2.0f)
            RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);
    }

    CWorld::pIgnoreEntity = e;
    if (CWorld::ProcessLineOfSight(targetCoords, cam->m_vecSource, colPoint, entity, true, true, true, true, false, true, true
#ifndef GTA3
        , false
#endif
    )) {
        cam->m_vecSource = colPoint.m_vecPoint;

        CVector d = cam->m_vecSource - targetCoords;
        float l = d.Magnitude();
        if (l > 0.3f) {
            d.x = d.x / l * (l - 0.3f);
            d.y = d.y / l * (l - 0.3f);
            d.z = d.z / l * (l - 0.3f);

        }
        cam->m_vecSource = targetCoords + d;

        if (Magnitude2d(targetCoords - cam->m_vecSource) < 2.0f)
            RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);
    }
    CWorld::pIgnoreEntity = NULL;

    GetVectorsReadyForRW();
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
