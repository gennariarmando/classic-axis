#pragma once

#include "CEntity.h"
#include "CStoredCollPoly.h"
#include "CSector.h"
#include "CCol.h"
#include "CPlayerInfo.h"

class CWorld {
public:
	// static variables
	static unsigned char &PlayerInFocus;
	static CPlayerInfo *Players;
	static bool &bDoingCarCollisions;
	static bool &bForceProcessControl;
	static bool &bIncludeCarTyres;
	static bool &bIncludeDeadPeds;
	static bool &bNoMoreCollisionTorque;
	static bool &bProcessCutsceneOnly;
	static bool &bSecondShift;
	static CSector *ms_aSectors;
	static CPtrList *ms_bigBuildingsList;
	static CPtrList *ms_listMovingEntityPtrs;
	static short  &ms_nCurrentScanCode;
	static CEntity *&pIgnoreEntity;
public:
	static bool ProcessLineOfSight(CVector const& origin, CVector const& target, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck);
};
