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

CColPoint* gaTempSphereColPoints = (CColPoint*)0x6E64C0;

void CCamNew::Process_FollowPed(CVector const& target, float targetOrient, float, float) {
	CPed* e = (CPed*)m_pCamTargetEntity;
	const char weaponType = e->m_aWeapons[e->m_nCurrentWeapon].m_eWeaponType;

	if (e->m_nType != ENTITY_TYPE_PED)
		return;

	m_fFOV = 70.0f;

	const float minDist = 2.0f;
	const float maxDist = 2.0f + TheCamera.m_fPedZoomValueSmooth;
	const float heightOffset = 0.5f;
	const bool aimingWeaponChanges = classicAxis.isAiming;
	const bool usingController = classicAxis.pXboxPad->HasPadInHands();

	RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);
	if (aimingWeaponChanges) {
		CVector aimOffset = CVector(0.5f, 0.0f, 0.5f);
		targetCoords = TransformFromObjectSpace(e->m_matrix, e->GetHeading(), aimOffset);

		CEntity* entity = NULL;
		CColPoint colPoint;

		if (CWorld::ProcessLineOfSight(targetCoords, m_vecSource, colPoint, entity, true, false, false, true, false, true, true)) {
			targetCoords = target;
		}

		wasAiming = true;
	}
	else {
		targetCoords = target;
		targetCoords.z += m_fSyphonModeTargetZOffSet;
	}

	targetCoords.z += heightOffset;

	CVector dist = m_vecSource - targetCoords;

	if (m_bResetStatics) {
		m_fHorizontalAngle = CGeneral::GetATanOfXY(-dist.x, -dist.y);
		m_fVerticalAngle = 0.0f;

		dist = maxDist * CVector(cosf(m_fVerticalAngle) * cosf(m_fHorizontalAngle), cosf(m_fVerticalAngle) * sinf(m_fHorizontalAngle), sinf(m_fVerticalAngle));
		m_vecSource = targetCoords + dist;

		m_bResetStatics = false;
	}

	float length = dist.Magnitude();
	if (length == 0.0f)
		dist = CVector(1.0f, 1.0f, 0.0f);
	else if (length < minDist)
		dist *= minDist / length;
	else if (length > maxDist)
		dist *= maxDist / length;

	if (aimingWeaponChanges) {
		length = minDist;
	}
	else {
		length = dist.Magnitude();

		if (wasAiming) {
			length = lengthBeforeAiming;
			wasAiming = false;
		}

		lengthBeforeAiming = length;
	}

	bool lockMovement = false;
	CEntity* p = e->m_pPointGunAt;
	if (CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_bHasLockOnTarget && !m_bLookingBehind && p) {
		CVector target = p->GetPosition();
		CVector targetDiff = (m_vecSource - target);

		m_fHorizontalAngle = CGeneral::GetATanOfXY(targetDiff.x, targetDiff.y) + M_PI;
		m_fVerticalAngle = CGeneral::GetATanOfXY(Magnitude2d(targetDiff), -targetDiff.z) + M_1_PI / 2;
		lockMovement = true;
	}
	else if (usingController && !aimingWeaponChanges && !m_bLookingBehind) {
		m_fHorizontalAngle = CGeneral::GetATanOfXY(-dist.x, -dist.y);
		m_fVerticalAngle = CGeneral::GetATanOfXY(Magnitude2d(dist), -dist.z);
	}

	if ((TheCamera.GetFading() && TheCamera.GetFadingDirection() == 1 && CDraw::FadeValue > 45) ||
		CDraw::FadeValue > 200) {
		lockMovement = true;
	}

	while (m_fHorizontalAngle >= M_PI) m_fHorizontalAngle -= 2.0f * M_PI;
	while (m_fHorizontalAngle < -M_PI) m_fHorizontalAngle += 2.0f * M_PI;
	while (m_fVerticalAngle >= M_PI) m_fVerticalAngle -= 2.0f * M_PI;
	while (m_fVerticalAngle < -M_PI) m_fVerticalAngle += 2.0f * M_PI;

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

	float betaOffset = lookLeftRight * 0.01f * (1.0f / 20.0f) * m_fFOV / 80.0f * CTimer::ms_fTimeStep;
	float alphaOffset = lookUpDown * 0.01f * (0.6f / 20.0f) * m_fFOV / 80.0f * CTimer::ms_fTimeStep;

	if (mouseInput) {
		betaOffset = lookLeftRight * TheCamera.m_fMouseAccelHorzntal * m_fFOV / 80.0f;
		alphaOffset = lookUpDown * TheCamera.m_fMouseAccelHorzntal * m_fFOV / 80.0f;
	}

	if (betaOffset || alphaOffset || lockMovement)
		m_bRotating = false;

	if (!lockMovement) {
		m_fHorizontalAngle += betaOffset;
		m_fVerticalAngle += alphaOffset;
	}

	while (m_fHorizontalAngle >= M_PI) m_fHorizontalAngle -= 2.0f * M_PI;
	while (m_fHorizontalAngle < -M_PI) m_fHorizontalAngle += 2.0f * M_PI;

	if (m_fVerticalAngle > DegToRad(60.0f))
		m_fVerticalAngle = DegToRad(60.0f);
	else if (m_fVerticalAngle < -DegToRad(89.5f))
		m_fVerticalAngle = -DegToRad(89.5f);

	if (CPad::GetPad(0)->ForceCameraBehindPlayer() && !lockMovement) {
		m_fTargetBeta = targetOrient;
		m_bRotating = true;
	}

	if (aimingWeaponChanges)
		m_bRotating = false;

	if (m_bRotating) {
		WellBufferMe(m_fTargetBeta, &m_fHorizontalAngle, &m_fBetaSpeed, 0.1f, 0.06f, true);
		float DeltaBeta = m_fTargetBeta - m_fHorizontalAngle;
		while (DeltaBeta >= M_PI) DeltaBeta -= 2 * M_PI;
		while (DeltaBeta < -M_PI) DeltaBeta += 2 * M_PI;
		if (abs(DeltaBeta) < 0.06f)
			m_bRotating = false;
	}

	if (TheCamera.m_bUseTransitionBeta)
		m_fHorizontalAngle = CGeneral::GetATanOfXY(-cos(m_fTransitionBeta), -sin(m_fTransitionBeta));
	
	m_fDistanceBeforeChanges = (m_vecSource - targetCoords).Magnitude();

	m_vecFront = CVector(cos(m_fVerticalAngle) * cos(m_fHorizontalAngle), cos(m_fVerticalAngle) * sin(m_fHorizontalAngle), sin(m_fVerticalAngle));
	m_vecSource = targetCoords - m_vecFront * length;
	m_vecSourceBeforeLookBehind = targetCoords + m_vecFront;
	targetCoords.z -= heightOffset;

	m_vecTargetCoorsForFudgeInter = targetCoords;

	m_vecFront = targetCoords - m_vecSource;
	m_vecFront.Normalise();

	CEntity* entity = NULL;
	CColPoint colPoint;
	CWorld::pIgnoreEntity = e;
	
	if (CWorld::ProcessLineOfSight(targetCoords, m_vecSource, colPoint, entity, true, true, false, true, false, true, true)) {
		m_vecSource = colPoint.m_vecPoint;

		CVector d = m_vecSource - targetCoords;
		float l = d.Magnitude();
		if (l > 0.4f) {
			d.x = d.x / l * (l - 0.3f);
			d.y = d.y / l * (l - 0.3f);
			d.z = d.z / l * (l - 0.3f);

		}
		m_vecSource = targetCoords + d;

		if (Magnitude2d(targetCoords - m_vecSource) < 2.0f)
			RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);
	}

	CWorld::pIgnoreEntity = e;
	if (CWorld::ProcessLineOfSight(targetCoords, m_vecSource, colPoint, entity, true, true, true, true, false, true, true)) {
		m_vecSource = colPoint.m_vecPoint;

		CVector d = m_vecSource - targetCoords;
		float l = d.Magnitude();
		if (l > 0.3f) {
			d.x = d.x / l * (l - 0.3f);
			d.y = d.y / l * (l - 0.3f);
			d.z = d.z / l * (l - 0.3f);

		}
		m_vecSource = targetCoords + d;

		if (Magnitude2d(targetCoords - m_vecSource) < 2.0f)
			RwCameraSetNearClipPlane(Scene.m_pCamera, 0.05f);
	}
	CWorld::pIgnoreEntity = NULL;

	GetVectorsReadyForRW();
}

void CCamNew::GetVectorsReadyForRW() {
	CVector right;
	m_vecUp = CVector(0.0f, 0.0f, 1.0f);
	m_vecFront.Normalise();
	if (m_vecFront.x == 0.0f && m_vecFront.y == 0.0f) {
		m_vecFront.x = 0.0001f;
		m_vecFront.y = 0.0001f;
	}
	right = CrossProduct(m_vecFront, m_vecUp);
	right.Normalise();
	m_vecUp = CrossProduct(right, m_vecFront);
}
