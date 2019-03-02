#pragma once

struct LimbOrientation {
	float m_fYaw;
	float m_fPitch;
};

VALIDATE_SIZE(LimbOrientation, 8);

struct LimbMovementInfo {
	float maxYaw;
	float minYaw;
	float yawD;
	float maxPitch;
	float minPitch;
	float pitchD;
};
VALIDATE_SIZE(LimbMovementInfo, 0x18);