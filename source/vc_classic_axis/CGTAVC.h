#pragma once
#define _USE_MATH_DEFINES
#include "math.h"
#pragma warning(disable:4480)
#define RADTODEG(x) (float)(180.0f*(x)/M_PI)
#define DEGTORAD(x) (float)((x)/180.0f*M_PI)

#define PI M_PI

#define WIN32_LEAN_AND_MEAN 

#define DebuggerBreak()	__asm int 3
#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)

#define VALIDATE_OFFSET(struc, member, offset) static_assert(offsetof(struc, member) == offset, "The offset of " #member " in " #struc " is not " #offset "...")    

#define ARRAY_SIZE(array)               (sizeof(array) / sizeof(array[0]))

#define _SWSTRING_INIT(str, id) std::wstring my_ws##id; for (size_t i = 0; i < strlen(str); i++) my_ws##id += str[i]
#define _SWSTRING(id) const_cast<wchar_t *>(my_ws##id.c_str())
#define LODWORD(_qw)    ((DWORD)(_qw))

#define _address(a, b, c, d, e, f) AddressByVersion<uintptr_t>(a, b, c, d, e, f)

#define PLUGIN_PATH(a) (GetPluginDirRelativePathA(a))

#include <windows.h>
#include "..\shared\CPatch.h"
#include "..\shared\Patterns.h"
#include "..\shared\GInputAPI.h"
#include "..\shared\ModuleList.h"

#include "CPlayerPed.h"
#include "CVehicle.h"

extern char *gString;
CPed *FindPlayerPed();
CVehicle *FindPlayerVehicle();
float FindPlayerHeading();
CVector *FindPlayerCentreOfWorld_NoSniperShift();
CVector *FindPlayerCentreOfWorld(int id);

char* GetPluginDirRelativePathA(char *substring);

extern IGInputPad* pXboxPad;
extern ModuleList moduleList;

static bool KeyPressed(unsigned int keyCode) {
	return (GetKeyState(keyCode) & 0x8000) != 0;
}

static unsigned __int8 AsciiToUnicode(const unsigned __int8 *a1, wchar_t *a2) {
	return ((unsigned __int8(__cdecl *)(const unsigned __int8 *, wchar_t *))0x5009C0)(a1, a2);
}

static unsigned __int64 myrand_seed = 1;

static int myrand(void) {
	myrand_seed = 0x5851F42D4C957F2D * myrand_seed + 1;
	return ((myrand_seed >> 32) & 0x7FFFFFFF);
}

static void mysrand(unsigned int seed) {
	myrand_seed = seed;
}

static int ReadHex(const char *str) {
	int n = 0;
	if (strlen(str) > 2)
		sscanf(str + 2, "%X", &n);
	return n;
}