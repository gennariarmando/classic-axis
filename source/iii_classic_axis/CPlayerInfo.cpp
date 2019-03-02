#include "CGTA3D.h"
#include "CPlayerInfo.h"

bool CPlayerInfo::IsPlayerInRemoteMode() {
	return ((bool(__thiscall *)(CPlayerInfo *))0x4A0930)(this);
}
