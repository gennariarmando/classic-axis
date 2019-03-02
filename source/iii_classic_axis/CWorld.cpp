#include "CGTA3D.h"
#include "CWorld.h"

unsigned char &CWorld::PlayerInFocus = *(unsigned char *)0x95CD61;
CPlayerInfo *CWorld::Players = (CPlayerInfo *)0x9412F0;
bool &CWorld::bDoingCarCollisions = *(bool *)0x95CD8C;
bool &CWorld::bForceProcessControl = *(bool *)0x95CD6C;
bool &CWorld::bIncludeCarTyres = *(bool *)0x95CDAA;
bool &CWorld::bIncludeDeadPeds = *(bool *)0x95CD8F;
bool &CWorld::bNoMoreCollisionTorque = *(bool *)0x95CDCC;
bool &CWorld::bProcessCutsceneOnly = *(bool *)0x95CD8B;
bool &CWorld::bSecondShift = *(bool *)0x95CD54;
CSector *CWorld::ms_aSectors = (CSector *)0x665608;
CPtrList *CWorld::ms_bigBuildingsList = (CPtrList *)0x6FAB60;
CPtrList *CWorld::ms_listMovingEntityPtrs = (CPtrList *)0x8F433C;
short &CWorld::ms_nCurrentScanCode = *(short *)0x95CC64;
CEntity *&CWorld::pIgnoreEntity = *(CEntity **)0x8F6494;

bool CWorld::ProcessLineOfSight(CVector const& origin, CVector const& target, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck) {
	return ((bool(__cdecl *)(CVector const&, CVector const&, CColPoint&, CEntity*&, bool, bool, bool, bool, bool, bool, bool))0x4AF970)(origin, target, outColPoint, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, doCameraIgnoreCheck);
}
