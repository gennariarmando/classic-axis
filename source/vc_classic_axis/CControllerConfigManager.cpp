#include "CGTAVC.h"
#include "CControllerConfigManager.h"

CControllerConfigManager* ControlsManager = (CControllerConfigManager*)0x8F43A4;

int CControllerConfigManager::SaveSettings(int hFile) {
	return ((int(__thiscall*)(CControllerConfigManager*, int))0x58B800)(this, hFile);
}

int CControllerConfigManager::LoadSettings(int hFile) {
	return ((int(__thiscall*)(CControllerConfigManager*, int))0x58B870)(this, hFile);
}
