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
    bool altKeyWalk;
    bool storiesAimingCoords;
    float cameraCrosshairMultX;
    float cameraCrosshairMultY;
    bool storiesPointingArm;
    float rightAnalogStickSensitivityX;
    float rightAnalogStickSensitivityY;

public:
    void Read();
};
