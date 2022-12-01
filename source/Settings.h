#pragma once

enum eLockOnTargetType {
    TARGET_DEFAULT,
    TARGET_SA,
    TARGET_LCS
};

enum eAimingCoords {
    COORDS_SA,
    COORDS_STORIES,
    COORDS_CUSTOM
};

class Settings {
public:
    bool forceAutoAim;
    int lockOnTargetType;
    bool showTriangleForMouseRecruit;
    std::string walkKey;
    int transitionSpeed;
    float aimingCoordsX;
    float aimingCoordsY;
    float aimingCoordsZ;
    int aimingCoords;
    float cameraCrosshairMultX;
    float cameraCrosshairMultY;
    bool storiesPointingArm;
    float rightAnalogStickSensitivityX;
    float rightAnalogStickSensitivityY;
    bool zoomForAssaultRifles;
#ifdef GTA3
    std::string crouchKey;
#endif

public:
    void Read();
};
