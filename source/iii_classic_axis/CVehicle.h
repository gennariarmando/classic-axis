#pragma once

#include "CPhysical.h"
#include "CCol.h"
#include "CDamageManager.h"
#include "eWeaponType.h"
#include "CStoredCollPoly.h"
#include "tHandlingData.h"
#include "CAutoPilot.h"
#include "CFire.h"

enum eCarWeapon {

};

enum eCarLock {
	CARLOCK_NOT_USED,
	CARLOCK_UNLOCKED,
	CARLOCK_LOCKED,
	CARLOCK_LOCKOUT_PLAYER_ONLY,
	CARLOCK_LOCKED_PLAYER_INSIDE,
	CARLOCK_COP_CAR,
	CARLOCK_FORCE_SHUT_DOORS,
	CARLOCK_SKIP_SHUT_DOORS
};

enum eVehicleType {
	VEHICLE_AUTOMOBILE,
	VEHICLE_BOAT,
	VEHICLE_TRAIN,
	VEHICLE_HELI,
	VEHICLE_PLANE,
	VEHICLE_BIKE
};

enum eVehicleLightsFlags {
	VEHICLE_LIGHTS_TWIN = 1,
	VEHICLE_LIGHTS_IGNORE_DAMAGE = 4,
	VEHICLE_LIGHTS_DISABLE_FRONT = 16,
	VEHICLE_LIGHTS_DISABLE_REAR = 32
};

enum eVehicleCreatedBy {
	RANDOM_VEHICLE = 1,
	MISSION_VEHICLE = 2,
	PARKED_VEHICLE = 3,
	PERMANENT_VEHICLE = 4
};

enum eBombState {
	BOMB_TIMED_NOT_ACTIVATED = 1,
	BOMB_IGNITION = 2,
	BOMB_STICKY = 3,
	BOMB_TIMED_ACTIVATED = 4,
	BOMB_IGNITION_ACTIVATED = 5
};

#if 0
enum eOrdnanceType;
enum eFlightModel;
enum eDoors;
#else
typedef int eOrdnanceType;
typedef int eFlightModel;
#endif

class CWeapon;
class CPed;
typedef int tWheelState;

class CVehicle : public CPhysical {
public:
	tHandlingData          *m_pHandling;
	CAutoPilot              m_autoPilot;
	unsigned char           m_nPrimaryColor;
	unsigned char           m_nSecondaryColor;
	unsigned char           m_nExtra[2];
	short                   m_nWantedStarsOnEnter;
	short                   m_nMissionValue;
	CPed                   *m_pDriver;
	CPed                   *m_pPassenger[8];
	unsigned char           m_nNumPassengers;
	char                    m_nNumGettingIn;
	char                    m_nGettingInFlags;
	char                    m_nGettingOutFlags;
	unsigned char           m_nNumMaxPassengers;
	char field_1CD[19];
	CEntity                *m_pRoad;
	CFire                  *m_pCarFire;
	float                   m_fSteerAngle;
	float                   m_fGasPedal;
	float                   m_fBreakPedal;
	unsigned char           m_nCreatedBy;        // see eVehicleCreatedBy
	struct {
		unsigned char bIsLawEnforcer : 1;
		unsigned char bIsAmbulanceOnDuty : 1;
		unsigned char bIsFireTruckOnDuty : 1;
		unsigned char bIsLocked : 1;
		unsigned char bEngineOn : 1;
		unsigned char b06 : 1;
		unsigned char bLightsOn : 1;
		unsigned char b08 : 1;

		unsigned char bIsVan : 1;
		unsigned char bIsBus : 1;
		unsigned char bIsBig : 1;
		unsigned char bIsLow : 1;
		unsigned char b13 : 1;
		unsigned char b14 : 1;
		unsigned char b15 : 1;
		unsigned char b16 : 1;

		unsigned char b17 : 1;
		unsigned char bIsDamaged : 1;
		unsigned char b19 : 1;
		unsigned char b20 : 1;
		unsigned char b21 : 1;
		unsigned char b22 : 1;
		unsigned char b23 : 1;
		unsigned char b24 : 1;

		unsigned char b25 : 1;
		unsigned char b26 : 1;
		unsigned char b27 : 1;
		unsigned char b28 : 1;
		unsigned char b29 : 1;
		unsigned char b30 : 1;
		unsigned char b31 : 1;
		unsigned char b32 : 1;
	} m_nVehicleFlags;
	char field_1F9;
	unsigned char           m_nAmmoInClip[1];    // Used to make the guns on boat do a reload (20 by default)
	char field_1FB;
	char field_1FC[4];
	float                   m_fHealth;           // 1000.0f = full health. 0 -> explode
	unsigned char           m_nCurrentGear;
	char field_205[3];
	int field_208;
	unsigned int            m_nGunFiringTime;    // last time when gun on vehicle was fired (used on boats)
	unsigned int            m_nTimeOfDeath;
	short field_214;
	short                   m_nBombTimer;        // goes down with each frame
	CPed                   *m_pWhoDetonatedMe;   // if vehicle was detonated, game copies m_pWhoInstalledBombOnMe here
	float field_21C;
	float field_220;
	unsigned int            m_nDoorLock;         // see enum eCarLock
	char                    m_nLastWeaponDamage; // see eWeaponType, -1 if no damage
	char                    m_nRadioStation;
	char field_22A;
	char field_22B;
	unsigned char           m_nCarHornTimer;
	char field_22D;
	unsigned char           m_nSirenOrAlarm;
	char field_22F;
	CStoredCollPoly         m_frontCollPoly;     // poly which is under front part of car
	CStoredCollPoly         m_rearCollPoly;      // poly which is under rear part of car
	float                   m_fSteerRatio;
	unsigned int            m_nVehicleClass;   // see enum eVehicleType

protected:
	CVehicle() : CPhysical() {}
public:


	CVehicle(const CVehicle &) = delete;
	CVehicle &operator=(const CVehicle &) = delete;

	static bool& m_bDisableMouseSteering;
	static bool& bWheelsOnlyCheat;
	static bool& bAllDodosCheat;
	static bool& bCheat3;

public:
	static char handlingnames[57][14];
	static int __fastcall SetEnvironmentMap(int, int);
};

VALIDATE_SIZE(CVehicle, 0x288);

extern float &fBurstTyreMod; // 0.1
extern float &fBurstSpeedMax; // 0.3