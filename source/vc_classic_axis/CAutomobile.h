#pragma once

#include "CVehicle.h"
#include "CDoor.h"
#include "eModelIndices.h"
#include "CWheel.h"

class CObject;

enum eCarNodes {
	CAR_NODE_NONE = 0,
	CAR_WHEEL_RF = 1,
	CAR_WHEEL_RM = 2,
	CAR_WHEEL_RB = 3,
	CAR_WHEEL_LF = 4,
	CAR_WHEEL_LM = 5,
	CAR_WHEEL_LB = 6,
	CAR_BUMP_FRONT = 7,
	CAR_BUMP_REAR = 8,
	CAR_WING_RF = 9,
	CAR_WING_RR = 10,
	CAR_DOOR_RF = 11,
	CAR_DOOR_RR = 12,
	CAR_WING_LF = 13,
	CAR_WING_LR = 14,
	CAR_DOOR_LF = 15,
	CAR_DOOR_LR = 16,
	CAR_BONNET = 17,
	CAR_BOOT = 18,
	CAR_WINDSCREEN = 19,
	CAR_NUM_NODES
};

class CAutomobile : public CVehicle {
protected:
	CAutomobile() : CVehicle() {}
public:
	CDamageManager m_carDamage;
	char bDamSwitch;
	char __f02B5[3];
	CDoor m_aDoors[6];
	RwFrame *m_aCarNodes[20];
	CWheel stWheels[4];
	int fWheelSuspDist[4];
	int fWheelSuspDistSoft[4];
	int fWheelContactRate[4];
	char __p04B0[28];
	int fWheelTotalRot[4];
	int fWheelRot[4];
	char __p04EC[4];
	int fNegSpeed;
	char __p04F4[9];
	char bfFlagsX;
	char __p04FE[46];
	int fWheelAngleMul;
	int fAIGripMultiplier;
	char __p0534[120];
	float m_fDoomHorizontalRotation;
	float m_fDoomVerticalRotation;
	int fSpecialSteering;
	int fSpecialMoveState;
	int uUnusedX;
	char nWheelsOnGround;
	char nRearWheelsOnGround;
	char bytePrevRearWheelsOnGround;
	char __f05C3;
	int fSkidMarkDensity;
	int nTireFriction[4];

	// variables
	static bool &m_sAllTaxiLights;
	static unsigned int &nGenerateRaindrops;
	static unsigned int &nGenerateWaterCircles;
	static CMatrix *matW2B;
};

VALIDATE_SIZE(CAutomobile, 0x5DC);