#include "CGTA3D.h"
#include "CVehicle.h"

bool& CVehicle::m_bDisableMouseSteering = *(bool *)0x60252C;
bool& CVehicle::bWheelsOnlyCheat = *(bool *)0x95CD78;
bool& CVehicle::bAllDodosCheat = *(bool *)0x95CD75;
bool& CVehicle::bCheat3 = *(bool *)0x95CD66;

float &fBurstTyreMod = *(float *)0x602538;
float &fBurstSpeedMax = *(float *)0x60253C;

static CPatch InjectPatches([]() {
	// Handling
	//memcpy((void*)0x6013E8, CVehicle::handlingnames, sizeof(CVehicle::handlingnames));
});

char CVehicle::handlingnames[57][14] = {
	"LANDSTAL",
	"RIVIERA", //"IDAHO",
	"STINGER",
	"FREIGHT", //"LINERUN",
	"NOVA", // "PEREN",
	"BEAMER", //"SENTINEL",
	"HUMVEE", //"PATRIOT",
	"FIRETRUK",
	"GARBAGE", //"TRASH",
	"LIMO", //"STRETCH",
	"RELIANT", //"MANANA",
	"INFERNUS",
	"CARRIER", //"BLISTA",
	"TRANSIT", //"PONY",
	"LUTON", //"MULE",
	"TESTEROS", //"CHEETAH",
	"AMBULAN",
	"FBICAR",
	"ASTROVAN", //"MOONBEAM",
	"ELDORADO", //"ESPERANT",
	"TAXI",
	"INTREPID", //"KURUMA",
	"PICKUP", //"BOBCAT",
	"ICECREAM", //"MRWHOOP",
	"BUGGY", //"BFINJECT",
	"POLICE",
	"SWATVAN", //"ENFORCER",
	"ARMOUR", //"SECURICA",
	"BANSHEE",
	"POLBOAT", //"PREDATOR",
	"BUS",
	"TANK", //"RHINO",
	"ARMYTRUK", //"BARRACKS",
	"SUBWAY", //"TRAIN",
	"HELI",
	"DODO",
	"COACH",
	"CABBIE",
	"STALLION",
	"RUMPO",
	"RCBANDIT",
	"BELLYUP",
	"MRWONGS",
	"MAFIA",
	"YARDIE",
	"YAKUZA",
	"DIABLOS",
	"COLUMB",
	"HOODS",
	"AIRTRAIN",
	"DEADDODO",
	"SPEEDER",
	"REEFER",
	"PANLANT",
	"FLATBED",
	"YANKEE",
	"BORGNINE",
};
