#pragma once

class CControllerConfigManager {
public:
	int SaveSettings(int hFile);
	int LoadSettings(int hFile);
};

extern CControllerConfigManager* ControlsManager;
