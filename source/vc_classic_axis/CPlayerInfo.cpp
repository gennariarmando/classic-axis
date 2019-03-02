#include "CGTAVC.h"
#include "CPlayerInfo.h"

bool CPlayerInfo::IsPlayerInRemoteMode() {
	return ((bool(__thiscall *)(CPlayerInfo *))0x4BCA60)(this);
}
