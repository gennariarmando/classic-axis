#pragma once

struct tTransmissionGear {
	float m_fMaxVelocity;
	float m_fChangeUpVelocity;
	float m_fChangeDownVelocity;
};

VALIDATE_SIZE(tTransmissionGear, 0xC);