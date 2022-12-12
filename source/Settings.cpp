#include "plugin.h"
#include "Settings.h"

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
    cameraCrosshairMultX = config["CameraCrosshairMultX"].asFloat(0.53f);
    cameraCrosshairMultY = config["CameraCrosshairMultY"].asFloat(0.4f);
    storiesPointingArm = config["StoriesPointingArm"].asBool(false);
    rightAnalogStickSensitivityX = config["RightAnalogStickSensitivityX"].asFloat(1.0f);
    rightAnalogStickSensitivityY = config["RightAnalogStickSensitivityY"].asFloat(1.0f);
    zoomForAssaultRifles = config["ZoomForAssaultRifles"].asBool(true);
    aimingCoords = config["AimingCoords"].asInt(COORDS_SA);
    aimingCoordsX = config["AimingCoordsX"].asFloat(0.0f);
    aimingCoordsY = config["AimingCoordsY"].asFloat(0.0f);
    aimingCoordsZ = config["AimingCoordsZ"].asFloat(0.0f);
    transitionSpeed = config["TransitionSpeed"].asInt(500);

#ifdef GTA3
    crouchKey = config["CrouchKey"].asString("C");
#endif
}
