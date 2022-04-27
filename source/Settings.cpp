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
    altKeyWalk = config["EnableLAltKeyWalk"].asBool(true);
    lcsAimingCoords = config["LCSAimingCoords"].asBool(false);
    cameraCrosshairMultX = config["CameraCrosshairMultX"].asFloat(0.53f);
    cameraCrosshairMultY = config["CameraCrosshairMultY"].asFloat(0.4f);
}
