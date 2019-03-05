#pragma once

class CMousePointerStateHelper {
public:
	char m_bInvertX;
	char m_bInvertY;

public:
	int GetMouseSetUp();
};

extern CMousePointerStateHelper &MousePointerHelper;

class CMouseControllerState {
public:
	unsigned char lmb;
	unsigned char rmb;
	unsigned char mmb;
	unsigned char wheelUp;
	unsigned char wheelDown;
	unsigned char bmx1;
	unsigned char bmx2;
	char _pad7;
	float X;
	float Y;
};

class CKeyboardState {
public:
	short FKeys[12];
	short standardKeys[256];
	short esc;
	short insert;
	short del;
	short home;
	short end;
	short pgup;
	short pgdn;
	short up;
	short down;
	short left;
	short right;
	short scroll;
	short pause;
	short numlock;
	short div;
	short mul;
	short sub;
	short add;
	short enter;
	short decimal;
	short num1;
	short num2;
	short num3;
	short num4;
	short num5;
	short num6;
	short num7;
	short num8;
	short num9;
	short num0;
	short back;
	short tab;
	short capslock;
	short extenter;
	short lshift;
	short rshift;
	short shift;
	short lctrl;
	short rctrl;
	short lmenu;
	short rmenu;
	short lwin;
	short rwin;
	short apps;
};

class CControllerState {
public:
	signed short LeftStickX; // move/steer left (-128?)/right (+128)
	signed short LeftStickY; // move back(+128)/forwards(-128?)
	signed short RightStickX; // numpad 6(+128)/numpad 4(-128?)
	signed short RightStickY;

	signed short LeftShoulder1;
	signed short LeftShoulder2;
	signed short RightShoulder1; // target / hand brake
	signed short RightShoulder2;

	signed short DPadUp; // radio change up           Next radio station / Call gang forward/Recruit gang member
	signed short DPadDown; // radio change down       Previous radio station / Gang stay back/Release gang (hold)
	signed short DPadLeft; //                         Skip trip/Action / Negative talk reply
	signed short DPadRight; //                        Next user MP3 track / Positive talk reply

	signed short Start;                             //Pause
	signed short Select;                            //Camera modes

	signed short ButtonSquare; // jump / reverse      Break/Reverse / Jump/Climb
	signed short ButtonTriangle; // get in/out        Exit vehicle / Enter veihcle
	signed short ButtonCross; // sprint / accelerate  Accelerate / Sprint/Swim
	signed short ButtonCircle; // fire                Fire weapon

	signed short ShockButtonL;
	signed short ShockButtonR; // look behind

	signed short m_bChatIndicated;
};

class CPad {
public:
	CControllerState NewState;
	CControllerState OldState;
	short SteeringLeftRightBuffer[10];
	int DrunkDrivingBufferUsed;
	CControllerState PCTempKeyState;
	CControllerState PCTempJoyState;
	CControllerState PCTempMouseState;
	short field_EA;
	short Mode;
	short ShakeDur;
	bool m_bDisablePlayerControls;
	char ShakeFreq;
	char bHornHistory[5];
	char iCurrHornHistory;
	char JustOutOfFrontEnd;
	char bApplyBrakes;
	char field_FB[12];
private:
	char _pad107;
public:
	int LastTimeTouched;
	int AverageWeapon;
	int AverageEntries;

	static CKeyboardState &NewKeyState;
	static CKeyboardState &OldKeyState;
	static CKeyboardState &TempKeyState;

	static char *KeyBoardCheatString;
	static bool &m_bMapPadOneToPadTwo;
	static bool &bDisplayNoControllerMessage;
	static bool &bObsoleteControllerMessage;

	static CMouseControllerState &PCTempMouseControllerState;
	static CMouseControllerState &NewMouseControllerState;
	static CMouseControllerState &OldMouseControllerState;

public:
	static short GetWeaponHook();
	static short WeaponJustDownHook();
	static short LookAroundLeftRightHook();
	static short LookAroundUpDownHook();
	static short GetPedWalkLeftRightHook(int _this, int);
	static short GetPedWalkUpDownHook(int _this, int);

public:
	int GetLookUpDown();
	int GetLookLeftRight();
	int GetWeapon();
	bool GetTarget();
	bool TargetJustDown();
	bool WeaponJustDown();
	bool GetWeaponTarget();
	int LookAroundUpDown();
	int LookAroundLeftRight();
	int GetLookBehindForPed();
	int GetLookBehindForCar();
	int GetPedWalkUpDown();
	int GetPedWalkLeftRight();
	bool ShiftTargetLeftJustDown();
	bool ShiftTargetRightJustDown();
	bool SecondaryFire();
	bool SecondaryFireJustDown();
	bool GetSprint();

	static CPad* GetPad(int padNumber);
};

extern CPad(&Pads)[2];
