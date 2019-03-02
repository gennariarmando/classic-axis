#include "CGTA3D.h"
#include "RenderWare.h"
#include "CWorld.h"
#include "CGeneral.h"
#include "CCam.h"
#include "CCamera.h"

static CPatch InjectPatches([]() {

});

CPed *FindPlayerPed() {
	return CWorld::Players[CWorld::PlayerInFocus].m_pPed;
}

CVehicle *FindPlayerVehicle() {
	if (FindPlayerPed() && FindPlayerPed()->m_bInVehicle)
		return FindPlayerPed()->m_pVehicle;
	else
		return false;
}

float FindPlayerHeading() {
	return ((float(__cdecl *)())_address(0x4A1220, 0, 0, 0, 0, 0))();
}

CVector *FindPlayerCentreOfWorld_NoSniperShift() {
	return ((CVector*(__cdecl *)())_address(0x4A11C0, 0, 0, 0, 0, 0))();
}

CVector *FindPlayerCentreOfWorld(int id) {
	return ((CVector*(__cdecl *)(int))_address(0x4A1170, 0, 0, 0, 0, 0))(id);
}

struct PluginPathA {
	char _path[MAX_PATH + 1];
	char _temp_path[MAX_PATH + 1];

	static void func() {}

	PluginPathA() {
		_path[0] = '\0';
		HMODULE h = NULL;
		if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
			(LPCSTR)&func, &h)) {

			MessageBoxA(NULL, "FILESYSTEM\nUnable to retrieve classic axis dir path", "classic axis", 0);

		}
		GetModuleFileNameA(h, _path, MAX_PATH);
		char *slp = strrchr(_path, '\\');
		if (slp)
			slp[1] = '\0';
	}
};

PluginPathA &PluginPathAInstance() {
	static PluginPathA pluginPath;
	return pluginPath;
}

char* GetPluginDirRelativePathA(char *subpath) {
	strcpy(PluginPathAInstance()._temp_path, PluginPathAInstance()._path);
	strcat(PluginPathAInstance()._temp_path, subpath);
	return PluginPathAInstance()._temp_path;
}
