#include "CGTAVC.h"
#include "CPad.h"
#include "CCamera.h"
#include "Settings.h"

CPad(&Pads)[2] = *reinterpret_cast<CPad(*)[2]>((0x7DBCB0));

CKeyboardState &CPad::NewKeyState = *(CKeyboardState *)0x7D15A8;
CKeyboardState &CPad::OldKeyState = *(CKeyboardState *)0x7DDB88;
CKeyboardState &CPad::TempKeyState = *(CKeyboardState *)0x864A00;

char *CPad::KeyBoardCheatString = (char *)0xA10942;
bool &CPad::m_bMapPadOneToPadTwo = *(bool *)0xA10AE4;
bool &CPad::bDisplayNoControllerMessage = *(bool *)0xA10AEC;
bool &CPad::bObsoleteControllerMessage = *(bool *)0xA10B83;

CMouseControllerState &CPad::PCTempMouseControllerState = *(CMouseControllerState *)0x7DD860;
CMouseControllerState &CPad::NewMouseControllerState = *(CMouseControllerState *)0x94D788;
CMouseControllerState &CPad::OldMouseControllerState = *(CMouseControllerState *)0x936908;

CMousePointerStateHelper &MousePointerHelper = *(CMousePointerStateHelper*)0x95CC8C;

static CPatch InjectPatches([]() {
	if (GetSetting.bProcess_FollowPed) {
		CPatch::RedirectCall(0x534B02, CPad::GetWeaponHook);
		CPatch::RedirectCall(0x534C6B, CPad::GetWeaponHook);
		CPatch::RedirectCall(0x534BBF, CPad::WeaponJustDownHook);
		CPatch::RedirectCall(0x534C3D, CPad::WeaponJustDownHook);
	}

	if (GetSetting.bProcess_FollowVeh) {
		CPatch::RedirectCall(0x4711F2, CPad::LookAroundLeftRightHook);
		CPatch::RedirectCall(0x47C062, CPad::LookAroundLeftRightHook);
		CPatch::RedirectCall(0x481F35, CPad::LookAroundLeftRightHook);
		CPatch::RedirectCall(0x482935, CPad::LookAroundLeftRightHook);
		CPatch::RedirectCall(0x471206, CPad::LookAroundUpDownHook);
		CPatch::RedirectCall(0x47C082, CPad::LookAroundUpDownHook);
		CPatch::RedirectCall(0x481F55, CPad::LookAroundUpDownHook);
		CPatch::RedirectCall(0x482955, CPad::LookAroundUpDownHook);
	}

	if ((ReadHex(GetSetting.keyWalk.c_str())) != 0) {
		CPatch::RedirectCall(0x471230, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x507C4A, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x507E04, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x496ED1, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x496E2A, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x5378F9, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x535F63, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x5357E7, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x535BBD, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x50A560, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x50A57E, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x535BD2, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x5357FD, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x535F79, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x53791B, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x507E2B, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x507C6E, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x471248, CPad::GetPedWalkUpDownHook);
	}
});

short CPad::GetWeaponHook() {
	if (Pads->m_bDisablePlayerControls == 1)
		return false;

	return CPad::GetPad(0)->GetWeapon();
}

short CPad::WeaponJustDownHook() {
	if (Pads->m_bDisablePlayerControls == 1)
		return false;

	return CPad::GetPad(0)->WeaponJustDown();
}

short CPad::LookAroundLeftRightHook() {
	if (Pads->m_bDisablePlayerControls)
		return 0;

	if (pXboxPad->HasPadInHands())
		return CPad::GetPad(0)->LookAroundLeftRight();

	return 0;
}

short CPad::LookAroundUpDownHook() {
	if (Pads->m_bDisablePlayerControls)
		return 0;

	if (pXboxPad->HasPadInHands())
		return CPad::GetPad(0)->LookAroundUpDown();

	return 0;
}

short CPad::GetPedWalkLeftRightHook(int _this, int) {
	if (Pads->m_bDisablePlayerControls)
		return 0;

	float fSpeed = 1.0f;

	if (KeyPressed(ReadHex(GetSetting.keyWalk.c_str())))
		fSpeed = 0.40f;

	if (pXboxPad->HasPadInHands())
		return Pads->GetPedWalkLeftRight();
	else
		return static_cast<short>((Pads->NewState.DPadRight * fSpeed - Pads->NewState.DPadLeft * fSpeed) / 2.0f);

	return 0;
}

short CPad::GetPedWalkUpDownHook(int _this, int) {
	if (Pads->m_bDisablePlayerControls)
		return 0;

	float fSpeed = 1.0f;

	if (KeyPressed(ReadHex(GetSetting.keyWalk.c_str())))
		fSpeed = 0.40f;

	if (pXboxPad->HasPadInHands())
		return Pads->GetPedWalkUpDown();
	else
		return static_cast<short>((Pads->NewState.DPadDown * fSpeed - Pads->NewState.DPadUp * fSpeed) / 2.0f);

	return 0;
}

CPad* CPad::GetPad(int padNumber) {
	return ((CPad*(__cdecl *)(int))0x4AB060)(padNumber);
}

int CPad::GetLookUpDown() {
	if (this->m_bDisablePlayerControls)
		return false;

	return 0;//pXboxPad->HasPadInHands() ? (CPad::GetPad(0)->NewState.RightStickY * 0.05f) : 0 - ((CPad::NewMouseControllerState.Y * 0.5f) * (TheCamera.m_fMouseAccelHorzntl * 260.0f));
}

int CPad::GetLookLeftRight() {
	if (this->m_bDisablePlayerControls)
		return false;

	return 0;//return pXboxPad->HasPadInHands() ? (CPad::GetPad(0)->NewState.RightStickX * 0.05f) : 0 + ((CPad::NewMouseControllerState.X * 0.5f)* (TheCamera.m_fMouseAccelHorzntl * 260.0f));
}

int CMousePointerStateHelper::GetMouseSetUp() {
	return ((int(__stdcall *)(CMousePointerStateHelper*))0x4ADA20)(this);
}

int CPad::GetWeapon() {
	return ((int(__thiscall *)(CPad*))0x4AA830)(this) || (CPed::m_bDoAiming ? (CPad::GetPad(0)->NewState.LeftShoulder1) : ((int(__thiscall *)(CPad*))0x4AA830)(this));
}

bool CPad::GetTarget() {
	return ((int(__thiscall *)(CPad*))0x4AA4D0)(this);
}

bool CPad::TargetJustDown() {
	return ((int(__thiscall *)(CPad*))0x4AA460)(this);
}

bool CPad::WeaponJustDown() {
	if (Pads[0].m_bDisablePlayerControls == 1)
		return false;

	return ((int(__thiscall *)(CPad*))0x4AA7B0)(this) || (CPed::m_bDoAiming ? (CPad::GetPad(0)->NewState.LeftShoulder1 != 0 && CPad::GetPad(0)->OldState.LeftShoulder1 == 0) : ((int(__thiscall *)(CPad*))0x4AA7B0)(this));
}

bool CPad::GetWeaponTarget() {
	if (Pads[0].m_bDisablePlayerControls == 1)
		return false;

	return (CPad::GetPad(0)->GetWeapon() || CPad::GetPad(0)->WeaponJustDown() || CPad::GetPad(0)->GetTarget()) || (CPad::GetPad(0)->GetWeapon() || CPad::GetPad(0)->WeaponJustDown() && CPad::GetPad(0)->GetTarget());
}

int CPad::LookAroundUpDown() {
	return ((int(__thiscall *)(CPad*))0x4A98F0)(this);
}

int CPad::LookAroundLeftRight() {
	return ((int(__thiscall *)(CPad*))0x4A9A80)(this);
}

int CPad::GetLookBehindForPed() {
	return ((int(__thiscall *)(CPad*))0x4AAC00)(this);
}

int CPad::GetLookBehindForCar() {
	return ((int(__thiscall *)(CPad*))0x4AAC30)(this);
}

int CPad::GetPedWalkUpDown() {
	return ((int(__thiscall *)(CPad*))0x4AAD40)(this);
}

int CPad::GetPedWalkLeftRight() {
	return ((int(__thiscall *)(CPad*))0x4AAE30)(this);
}
