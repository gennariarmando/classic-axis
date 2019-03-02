#include "CGTAVC.h"
#include "CWorld.h"

unsigned int MAX_PLAYERS = 1;
// variables
CPlayerInfo *CWorld::Players = (CPlayerInfo *)0x94AD28;
unsigned char &CWorld::PlayerInFocus = *(unsigned char *)0xA10AFB;
CPtrList& CWorld::ms_listMovingEntityPtrs = *(CPtrList*)0x9B48A8;
CPtrList(&CWorld::ms_bigBuildingsList)[3] = *(CPtrList(*)[3])*(int *)0x9785FC;
bool &CWorld::bDoingCarCollisions = *(bool *)0x9B6E58;
short &CWorld::ms_nCurrentScanCode = *(short *)0xA1098E;
bool &CWorld::bIncludeDeadPeds = *(bool *)0xA10AEE;
bool &CWorld::bProcessCutsceneOnly = *(bool *)0xA10B1C;
CEntity*& CWorld::pIgnoreEntity = *(CEntity**)0x9B6E58;
bool &CWorld::bIncludeBikers = *(bool *)0xA10B48;
bool &CWorld::bNoMoreCollisionTorque = *(bool *)0xA10B49;
bool &CWorld::bForceProcessControl = *(bool *)0xA10B4A;
bool &CWorld::bSecondShift = *(bool *)0xA10B70;
bool &CWorld::bIncludeCarTyres = *(bool *)0xA10B96;
CSector(&CWorld::ms_aSectors)[6400] = *(CSector(*)[6400])*(int *)0x792D30;

bool CWorld::ProcessLineOfSight(CVector const& origin, CVector const& target, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck) {
	return ((bool(__cdecl *)(CVector const&, CVector const&, CColPoint&, CEntity*&, bool, bool, bool, bool, bool, bool, bool))0x4D92D0)(origin, target, outColPoint, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, doCameraIgnoreCheck);
}
