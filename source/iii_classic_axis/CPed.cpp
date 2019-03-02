#include "CGTA3D.h"
#include "CPed.h"
#include "CCamera.h"
#include "CWorld.h"

CVector *vecPedCarDoorAnimOffset = (CVector *)0x62E030;
CVector *vecPedCarDoorLoAnimOffset = (CVector *)0x62E03C;
CVector *vecPedVanRearDoorAnimOffset = (CVector *)0x62E048;
CVector *vecPedTrainDoorAnimOffset = (CVector *)0x62E054;
CVector *vecPedDraggedOutCarAnimOffset = (CVector *)0x62E060;
CVector *vecPedQuickDraggedOutCarAnimOffset = (CVector *)0x62E06C;

bool CPed::m_bDoAiming;
bool CPed::m_bHideCrosshair = false;

static CPatch InjectPatches([]() {

});

bool CPed::BeQuiteAndEasy() {
	int s = FindPlayerPed()->m_eState;
	return (s >= STATE_JUMPING && s <= STATE_INVEHICLE ||
		s == STATE_SEEK_CAR || s == STATE_SEEK_BOAT || s == STATE_GETTING_UP || s == STATE_ON_FIRE);
}

bool CPed::CanWeRunAndFireWithWeapon() {
	int weaponType = CWorld::Players[0].m_pPed->m_aWeapons[CWorld::Players[0].m_pPed->m_nWepSlot].m_nType;

	return weaponType == WEAPONTYPE_COLT45 || weaponType == WEAPONTYPE_UZI;
}

bool CPed::CanStrafeOrMouseControl() {
	ePedState state = this->m_eState;

	return state == STATE_IDLE || (state - STATE_FLEE_POSITION) <= 1 ||
		state == STATE_NONE || state == STATE_POINT_GUN ||
		(state - STATE_ATTACK) <= 1 || state == STATE_JUMPING || state == STATE_INVEHICLE;
}

void CPed::SetAimFlag(float heading) {
	((void(__thiscall *)(CPed *, float))0x4C6960)(this, heading);
}
	
char CPed::ClearLookFlag() {
	return ((char(__thiscall *)(CPed *))0x4C64F0)(this);
}

void CPed::SetPointGunAt(CEntity* entity) {
	((void(__thiscall *)(CPed *, CEntity*))0x4E5F70)(this, entity);
}

void CPed::AimGun() {
	((void(__thiscall *)(CPed *))0x4C6AA0)(this);
}

void CPed::ClearPointGunAt() {
	((void(__thiscall *)(CPed *))0x4E6180)(this);
}

void CPed::ClearAimFlag() {
	((void(__thiscall *)(CPed *))0x4C6A50)(this);
}

void CPed::ClearAll() {	
	((void(__thiscall *)(CPed *))0x4C7F20)(this);
}

void CPed::RestorePreviousState() {
	((void(__thiscall *)(CPed *))0x4C5E30)(this);
}

int CPed::SetAttackTimer(unsigned int time) {
	return ((int(__thiscall *)(CPed *, unsigned int))0x4D1300)(this, time);
}

int CPed::SetShootTimer(unsigned int time) {
	return ((int(__thiscall *)(CPed *, unsigned int))0x4D1340)(this, time);
}

void CPed::Say(unsigned short arg0) {
	((void(__thiscall *)(CPed *, unsigned int))0x4E5A10)(this, arg0);
}
