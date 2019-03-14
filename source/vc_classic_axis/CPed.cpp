#include "CGTAVC.h"
#include "CPed.h"
#include "CCamera.h"
#include "CWorld.h"
#include "Settings.h"

bool CPed::m_bDoAiming;
bool CPed::m_bHideCrosshair = false;

static CPatch InjectPatches([]() {
	if (GetSetting.bProcess_FollowPed) {
		CPatch::RedirectCall(0x52C274, CPed::CleanAimFlagHook);
	}
});

void __fastcall CPed::CleanAimFlagHook(int, int) {
	if (CPed::m_bDoAiming && (bool)!Pads->GetWeapon() && FindPlayerPed()->m_aWeapons[FindPlayerPed()->m_nWepSlot].m_nState != WEAPONSTATE_RELOADING)
		FindPlayerPed()->SetPointGunAt(0);

	FindPlayerPed()->ClearAimFlag();
}

bool CPed::BeQuiteAndEasy() {
	int s = FindPlayerPed()->m_eState;
	return (s >= STATE_JUMPING && s <= STATE_INVEHICLE ||
		s == STATE_SEEK_CAR || s == STATE_SEEK_BOAT || s == STATE_GETTING_UP || s == STATE_ON_FIRE);
}

bool CPed::CanWeRunAndFireWithWeapon() {
	int w = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_aWeapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_nWepSlot].m_nType;

	return	w == WEAPONTYPE_PISTOL || w == WEAPONTYPE_TEC9 ||
			w == WEAPONTYPE_UZI || w == WEAPONTYPE_SILENCED_INGRAM;
}

bool CPed::HeavyWeapons() {
	int w = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_aWeapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_nWepSlot].m_nType;

	return	w == WEAPONTYPE_PYTHON || w == WEAPONTYPE_SHOTGUN ||
		w == WEAPONTYPE_SPAS12_SHOTGUN || w == WEAPONTYPE_STUBBY_SHOTGUN ||
		w == WEAPONTYPE_MP5 || w >= WEAPONTYPE_M4 && w <= WEAPONTYPE_MINIGUN;
}

bool CPed::FirstPersonWeapons() {
	int w = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_aWeapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_nWepSlot].m_nType;

	return w == WEAPONTYPE_ROCKETLAUNCHER || w == WEAPONTYPE_SNIPERRIFLE || w == WEAPONTYPE_LASERSCOPE;
}

bool CPed::IsTypeMelee() {
	int w = CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_aWeapons[CWorld::Players[CWorld::PlayerInFocus].m_pPed->m_nWepSlot].m_nType;

	return w >= WEAPONTYPE_UNARMED && w <= WEAPONTYPE_ROCKET;
}

bool CPed::CanStrafeOrMouseControl() {
	ePedState state = this->m_eState;

	return state == STATE_IDLE || (state - STATE_FLEE_POSITION) <= 1 ||
		state == STATE_NONE || state == STATE_POINT_GUN ||
		(state - STATE_ATTACK) <= 1 || state == STATE_JUMPING || state == STATE_INVEHICLE;
}

void CPed::SetAimFlagToEntity(CEntity* e) {
	((void(__thiscall *)(CPed *, CEntity*))0x50B510)(this, e);
}

void CPed::SetAimFlag(float heading) {
	((void(__thiscall *)(CPed *, float))0x50B5B0)(this, heading);
}

void CPed::Attack() {
	((void(__thiscall *)(CPed *))0x52B070)(this);
}

void CPed::RestoreHeadingRate() {
	((void(__thiscall *)(CPed *))0x4F17D0)(this);
}

char CPed::ClearLookFlag() {
	return ((char(__thiscall *)(CPed *))0x50B9C0)(this);
}

void CPed::SetPointGunAt(CEntity* entity) {
	((void(__thiscall *)(CPed *, CEntity*))0x52DDF0)(this, entity);
}

void CPed::ClearAttack() {
	((void(__thiscall *)(CPed *))0x52D120)(this);
}

void CPed::ClearWaitState() {
	((void(__thiscall *)(CPed *))0x4F3130)(this);
}

void CPed::AimGun() {
	((void(__thiscall *)(CPed *))0x50B2C0)(this);
}

void CPed::ClearPointGunAt() {
	((void(__thiscall *)(CPed *))0x52DBE0)(this);
}

void CPed::ClearAimFlag() {
	((void(__thiscall *)(CPed *))0x50B4A0)(this);
}

void CPed::ClearAll() {
	((void(__thiscall *)(CPed *))0x509DF0)(this);
}

void CPed::RestorePreviousState() {
	((void(__thiscall *)(CPed *))0x50C600)(this);
}

int CPed::SetAttack(CEntity* e) {
	return ((int(__thiscall *)(CPed *, CEntity*))0x52D1C0)(this, e);
}

int CPed::SetAttackTimer(unsigned int time) {
	return ((int(__thiscall *)(CPed *, unsigned int))0x4FCAB0)(this, time);
}

int CPed::SetShootTimer(unsigned int time) {
	return ((int(__thiscall *)(CPed *, unsigned int))0x4FCA90)(this, time);
}

void CPed::Say(unsigned short arg0) {
	((void(__thiscall *)(CPed *, unsigned int))0x5226B0)(this, arg0);
}

void CPed::SetDuck(int unk, int unk2) {
	((void(__thiscall *)(CPed *, int, int))0x512C10)(this, unk, unk2);
}

void CPed::Duck() {
	((void(__thiscall *)(CPed *))0x512A90)(this);
}


void CPed::RemoveWeaponAnims(int a2, float a3) {
	((void(__thiscall *)(CPed *, int, float))0x5229B0)(this, a2, a3);
}

void CPed::Teleport(CVector posn) {
	((void(__thiscall *)(CPed *, CVector))0x4F5690)(this, posn);
}