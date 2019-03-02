#include "CGTA3D.h"
#include "CMenuPage.h"
#include "Settings.h"

const CMenuScreen CMenuPage::ControllerSetup = {
	 "FET_CTL", 41, 41, 41, 0, 0,
	{
		 72, "FET_RDK", 0,  55,
		  2, "FET_AMS", 0,  56,
		 98, "FET_DEF", 0,  35,
		  2, "FEDS_TB", 0,   0,
	}
};

static CPatch InjectPatches([]() {
	if (GetSetting.bProcess_FollowPed)
		CPatch::Set(0x611930 + sizeof(CMenuScreen) * 35, CMenuPage::ControllerSetup);
});
