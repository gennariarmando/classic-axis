#pragma once

enum eLockOnTargetType {
    TARGET_DEFAULT,
    TARGET_SA,
    TARGET_LCS
};

class Settings {
public:
    bool forceAutoAim;
    int lockOnTargetType;
    bool showTriangleForMouseRecruit;
    std::string walkKey;
    bool storiesAimingCoords;
    float cameraCrosshairMultX;
    float cameraCrosshairMultY;
    bool storiesPointingArm;
    float rightAnalogStickSensitivityX;
    float rightAnalogStickSensitivityY;
#ifdef GTA3
    std::string crouchKey;
#endif

public:
    void Read();
};
