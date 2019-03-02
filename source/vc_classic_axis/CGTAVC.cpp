#include "CGTAVC.h"
#include "RenderWare.h"
#include "CWorld.h"
#include "CGeneral.h"
#include "CCam.h"
#include "CCamera.h"

CPed *FindPlayerPed() {
	return ((CPed*(__cdecl *)())(0x4BC120))();
}

CVehicle *FindPlayerVehicle() {
	if (CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle)
		return CWorld::Players[CWorld::PlayerInFocus].m_pRemoteVehicle;

	return ((CVehicle*(__cdecl *)())(0x4BC1E0))();
}

float FindPlayerHeading() {
	return ((float(__cdecl *)())(0x4BBF70))();
}

CVector *FindPlayerCentreOfWorld_NoSniperShift() {
	return ((CVector*(__cdecl *)())(0x4BC020))();
}

CVector *FindPlayerCentreOfWorld(int id) {
	return ((CVector*(__cdecl *)(int))(0x4BC0A0))(id);
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
