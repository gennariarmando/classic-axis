#include "plugin.h"
#include "Settings.h"

Settings settings;

void Settings::Read() {
#ifdef GTA3
    plugin::config_file config(PLUGIN_PATH("ClassicAxisIII.ini"));
#else
    plugin::config_file config(PLUGIN_PATH("ClassicAxisVC.ini"));
#endif

    forceAutoAim = config["ForceAutoAim"].asBool(false);
    lockOnTargetType = config["LockOnTargetType"].asInt(TARGET_SA);
    showTriangleForMouseRecruit = config["ShowTriangleForMouseRecruit"].asBool(true);
    walkKey = config["WalkKey"].asString("LALT");
    storiesAimingCoords = config["StoriesAimingCoords"].asBool(false);
    cameraCrosshairMultX = config["CameraCrosshairMultX"].asFloat(0.53f);
    cameraCrosshairMultY = config["CameraCrosshairMultY"].asFloat(0.4f);
    storiesPointingArm = config["StoriesPointingArm"].asBool(false);
    rightAnalogStickSensitivityX = config["RightAnalogStickSensitivityX"].asFloat(1.0f);
    rightAnalogStickSensitivityY = config["RightAnalogStickSensitivityY"].asFloat(1.0f);
    zoomForAssaultRifles = config["ZoomForAssaultRifles"].asBool(true);
    modernCamera = config["ModernCamera"].asBool(true);
#ifdef GTA3
    crouchKey = config["CrouchKey"].asString("C");
#endif
}
