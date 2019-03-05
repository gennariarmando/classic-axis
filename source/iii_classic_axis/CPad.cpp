#include "CGTA3D.h"
#include "CPad.h"
#include "CCamera.h"
#include "Settings.h"

short &CPad::ReconState = *(short *)0x628E64;
short &CPad::GetAnaloguePadUp_oldfStickY = *(short*)0x628E9A;
short &CPad::GetAnaloguePadDown_oldfStickY = *(short *)0x628E9E;
short &CPad::GetAnaloguePadLeft_oldfStickX = *(short *)0x628EA2;
short &CPad::GetAnaloguePadRight_oldfStickX = *(short *)0x628EA6;
short &CPad::GetAnaloguePadLeftJustUp_oldfStickX = *(short *)0x628EAA;
short &CPad::GetAnaloguePadRightJustUp_oldfStickX = *(short *)0x628EAE;

CPad(&Pads)[2] = *reinterpret_cast<CPad(*)[2]>((0x6F0360));

CKeyboardState &CPad::NewKeyState = *(CKeyboardState *)0x6E60D0;
CKeyboardState &CPad::OldKeyState = *(CKeyboardState *)0x6F1E70;
CKeyboardState &CPad::TempKeyState = *(CKeyboardState *)0x774DE8;

char *CPad::KeyBoardCheatString = (char *)0x885B90;
bool &CPad::m_bMapPadOneToPadTwo = *(bool *)0x95CD48;
bool &CPad::bDisplayNoControllerMessage = *(bool *)0x95CD52;
bool &CPad::bObsoleteControllerMessage = *(bool *)0x95CDB8;

CMouseControllerState &CPad::PCTempMouseControllerState = *(CMouseControllerState *)0x6F1E60;
CMouseControllerState &CPad::NewMouseControllerState = *(CMouseControllerState *)0x8809F0;
CMouseControllerState &CPad::OldMouseControllerState = *(CMouseControllerState *)0x8472A0;

CMousePointerStateHelper &MousePointerHelper = *(CMousePointerStateHelper*)0x95CC8C;

static CPatch InjectPatches([]() {
	if (GetSetting.bProcess_FollowPed) {
		CPatch::RedirectCall(0x4F203A, CPad::GetWeaponHook);
		CPatch::RedirectCall(0x4F20AB, CPad::GetWeaponHook);
		CPatch::RedirectCall(0x4F20DB, CPad::WeaponJustDownHook);
		CPatch::RedirectCall(0x4F2086, CPad::WeaponJustDownHook);
	}

	if (GetSetting.bProcess_FollowVeh) {
		CPatch::RedirectCall(0x45A1C8, CPad::LookAroundLeftRightHook);
		CPatch::RedirectCall(0x45AF7A, CPad::LookAroundLeftRightHook);
		CPatch::RedirectCall(0x46007A, CPad::LookAroundLeftRightHook);
		CPatch::RedirectCall(0x468E5D, CPad::LookAroundLeftRightHook);
		CPatch::RedirectCall(0x45A1E8, CPad::LookAroundUpDownHook);
		CPatch::RedirectCall(0x45AF9A, CPad::LookAroundUpDownHook);
		CPatch::RedirectCall(0x46009A, CPad::LookAroundUpDownHook);
		CPatch::RedirectCall(0x468E71, CPad::LookAroundUpDownHook);
	}	

	if ((ReadHex(GetSetting.keyWalk.c_str())) != 0) {
		CPatch::RedirectCall(0x493CEA, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x4F13E2, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x487ED6, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x4CA5CF, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x468EA4, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x493C8A, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x4F1987, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x4CA779, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x487E51, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x493D4A, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x493C2A, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x4F3226, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x4F181D, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x4C791A, CPad::GetPedWalkLeftRightHook);
		CPatch::RedirectCall(0x4F3246, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x4C7938, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x4F1832, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x4F13F8, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x4CA5F3, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x468EBC, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x4CA7A0, CPad::GetPedWalkUpDownHook);
		CPatch::RedirectCall(0x4F199D, CPad::GetPedWalkUpDownHook);
	}
});

short CPad::GetWeaponHook() {
	if (Pads->m_bDisablePlayerControls == 1)
		return false;

	return Pads->GetWeapon();
}

short CPad::WeaponJustDownHook() {
	if (Pads->m_bDisablePlayerControls == 1)
		return false;

	return Pads->WeaponJustDown();
}

short CPad::LookAroundLeftRightHook() {
	if (Pads->m_bDisablePlayerControls)
		return 0;

	if (pXboxPad->HasPadInHands())
		return Pads->LookAroundLeftRight();

	return 0;
}

short CPad::LookAroundUpDownHook() {
	if (Pads->m_bDisablePlayerControls)
		return 0;

	if (pXboxPad->HasPadInHands())
		return Pads->LookAroundUpDown();

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
	return ((CPad*(__cdecl *)(int))0x492F60)(padNumber);
}

int CPad::GetLookUpDown() {
	if (this->m_bDisablePlayerControls)
		return false;

	return 0;
}

int CPad::GetLookLeftRight() {
	if (this->m_bDisablePlayerControls)
		return false;

	return 0;
}

int CMousePointerStateHelper::GetMouseSetUp() {
	return ((int(__stdcall *)(CMousePointerStateHelper*))0x491BD0)(this);
}

int CPad::GetWeapon() {
	return ((int(__thiscall *)(CPad*))0x4936C0)(this) || (CPed::m_bDoAiming ? (SecondaryFire()) : ((int(__thiscall *)(CPad*))0x4936C0)(this));
}

bool CPad::GetTarget() {
	return ((int(__thiscall *)(CPad*))0x493970)(this);
}

bool CPad::TargetJustDown() {
	return ((int(__thiscall *)(CPad*))0x4939D0)(this);
}

bool CPad::WeaponJustDown() {
	if (this->m_bDisablePlayerControls)
		return false;

	return ((int(__thiscall *)(CPad*))0x493700)(this) || (CPed::m_bDoAiming ? (SecondaryFireJustDown()) : ((int(__thiscall *)(CPad*))0x493700)(this));
}

bool CPad::GetWeaponTarget() {
	if (this->m_bDisablePlayerControls)
		return false;

	return (Pads->GetWeapon() || Pads->WeaponJustDown() || Pads->GetTarget()) || (Pads->GetWeapon() || Pads->WeaponJustDown() && Pads->GetTarget());
}

int CPad::LookAroundUpDown() {
	return ((int(__thiscall *)(CPad*))0x494130)(this);
}

int CPad::LookAroundLeftRight() {
	return ((int(__thiscall *)(CPad*))0x493F80)(this);
}

int CPad::GetLookBehindForPed() {
	return ((int(__thiscall *)(CPad*))0x493320)(this);
}

int CPad::GetLookBehindForCar() {
	return ((int(__thiscall *)(CPad*))0x4932F0)(this);
}

int CPad::GetPedWalkUpDown() {
	return ((int(__thiscall *)(CPad*))0x493190)(this);
}

int CPad::GetPedWalkLeftRight() {
	return ((int(__thiscall *)(CPad*))0x493110)(this);
}

bool CPad::ShiftTargetLeftJustDown() {
	return ((bool(__thiscall *)(CPad*))0x493AE0)(this);

	return 0;
}

bool CPad::ShiftTargetRightJustDown() {
	return ((bool(__thiscall *)(CPad*))0x493B10)(this);

	return 0;
}

bool CPad::SecondaryFire() {
	if (m_bDisablePlayerControls)
		return false;

	if (Mode != 4)
		return NewState.LeftShoulder1;
}

bool CPad::SecondaryFireJustDown() {
	if (m_bDisablePlayerControls)
		return false;

	if (Mode != 4)
		return NewState.LeftShoulder1 != 0 && OldState.LeftShoulder1 == 0;
}

bool CPad::GetSprint() {
	return ((bool(__thiscall *)(CPad*))0x493A70)(this);
}
