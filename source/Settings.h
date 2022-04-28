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
    bool lcsAimingCoords;
    float cameraCrosshairMultX;
    float cameraCrosshairMultY;

public:
    void Read();
};
