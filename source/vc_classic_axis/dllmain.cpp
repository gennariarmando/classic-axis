#include "CGTAVC.h"
#include "Settings.h"

IGInputPad* pXboxPad;

BOOL WINAPI DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		GetSetting.ReadSettings();
		GInput_Load(&pXboxPad);

		if (GetSetting.bEnable)
			CPatch::Inject();
	}
	return TRUE;
}