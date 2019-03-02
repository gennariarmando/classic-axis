#include "CGTAVC.h"
#include "Config.h"
#include "Settings.h"

Settings GetSetting;

void Settings::ReadSettings() {
	config::config_file settings(PLUGIN_PATH("vc_classic_axis.ini"));

	// Main
	bEnable = settings["bEnable"].asBool(false);

	// Camera
	bProcess_FollowPed = settings["bProcess_FollowPed"].asBool(false);
	bProcess_FollowVeh = settings["bProcess_FollowVeh"].asBool(false);

	// GInput
	fRightStickVerticalSensitivity = settings["fRightStickVerticalSensitivity"].asFloat(0.0f);
	fRightStickHorizontalSensitivity = settings["fRightStickHorizontalSensitivity"].asFloat(0.0f);

	// Misc
	bControlVehParts = settings["bControlVehParts"].asBool(false);
	bForceAutoAim = settings["bForceAutoAim"].asBool(false);
	bNoAutoFoc = settings["bNoAutoFoc"].asBool(false);
	keyWalk = settings["keyWalk"].asString((char*)"");
	bIVOnFootCamera = settings["bIVOnFootCamera"].asBool(false);
	bIVVehicleCamera = settings["bIVVehicleCamera"].asBool(false);
	bDynamicFOV = settings["bDynamicFOV"].asBool(false);
	fFOV = settings["fFOV"].asFloat(0.0f);

	// Black list
	ModelID[0] = settings["ModelID0"].asInt(1);
	ModelID[1] = settings["ModelID1"].asInt(1);
	ModelID[2] = settings["ModelID2"].asInt(1);
	ModelID[3] = settings["ModelID3"].asInt(1);
	ModelID[4] = settings["ModelID4"].asInt(1);
	ModelID[5] = settings["ModelID5"].asInt(1);
	ModelID[6] = settings["ModelID6"].asInt(1);
	ModelID[7] = settings["ModelID7"].asInt(1);
	ModelID[8] = settings["ModelID8"].asInt(1);
	ModelID[9] = settings["ModelID9"].asInt(1);
	ModelID[10] = settings["ModelID10"].asInt(1);
	ModelID[11] = settings["ModelID11"].asInt(1);
	ModelID[12] = settings["ModelID12"].asInt(1);
	ModelID[13] = settings["ModelID13"].asInt(1);
	ModelID[14] = settings["ModelID14"].asInt(1);
	ModelID[15] = settings["ModelID15"].asInt(1);
	ModelID[16] = settings["ModelID16"].asInt(1);
	ModelID[17] = settings["ModelID17"].asInt(1);
	ModelID[18] = settings["ModelID18"].asInt(1);
	ModelID[19] = settings["ModelID19"].asInt(1);
	ModelID[20] = settings["ModelID20"].asInt(1);
}
