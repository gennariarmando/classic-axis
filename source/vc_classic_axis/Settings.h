#pragma once

class Settings {
public:
	bool bEnable;

	bool bProcess_FollowPed;
	bool bProcess_FollowVeh;

	float fRightStickVerticalSensitivity;
	float fRightStickHorizontalSensitivity;

	bool bControlVehParts;
	bool bForceAutoAim;
	bool bNoAutoFoc;
	std::string keyWalk;
	bool bIVOnFootCamera;
	bool bIVVehicleCamera;
	bool bDynamicFOV;
	float fFOV;

	int ModelID[20];

public:
	void ReadSettings();
};

extern Settings GetSetting;