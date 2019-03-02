#include "CGTAVC.h"
#include "CMenuPage.h"
#include "Settings.h"

const CMenuScreen CMenuPage::ControllerSetup = {
	"FET_CTL", 27, 0,
	{
		{ 35, "FEC_RED", 0, 30, 320, 150, 3 },
		{ 04, "FEC_MOU", 0, 31,   0,   0, 3 },
		{ 47, "FET_DEF", 0, 26,   0,   0, 3 },
		{ 34, "FEDS_TB", 0, 0,    0,   0, 3 },
	}
};

static CPatch InjectPatches([]() {
	if (GetSetting.bProcess_FollowPed)
		CPatch::Set(0x006D8B70 + sizeof(CMenuScreen) * 26, CMenuPage::ControllerSetup);
});
