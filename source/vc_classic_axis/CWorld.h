#pragma once

#include "CEntity.h"
#include "CStoredCollPoly.h"
#include "CSector.h"
#include "CCol.h"
#include "CPlayerInfo.h"

class CWorld {
public:
	// static variables
	// Player data array for 1 player.
	static CPlayerInfo *Players;
	static unsigned char &PlayerInFocus;
	static CPtrList& ms_listMovingEntityPtrs;		// CPtrList CWorld::ms_listMovingEntityPtrs
	static CPtrList(&ms_bigBuildingsList)[3];		// CPtrList CWorld::ms_bigBuildingsList[3]
	static bool &bDoingCarCollisions;
	static short &ms_nCurrentScanCode;
	static bool &bIncludeDeadPeds;
	static bool &bProcessCutsceneOnly;
	static CEntity*& pIgnoreEntity;		// CEntity* CWorld::pIgnoreEntity
	static bool &bIncludeBikers;
	static bool &bNoMoreCollisionTorque;
	static bool &bForceProcessControl;
	static bool &bSecondShift;
	static bool &bIncludeCarTyres;
	static CSector(&ms_aSectors)[6400];		// CSector CWorld::ms_aSectors[6400]

	static bool ProcessLineOfSight(CVector const& origin, CVector const& target, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck);
};

extern unsigned int MAX_PLAYERS; // 1