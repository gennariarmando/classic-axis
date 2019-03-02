#include "CGTA3D.h"
#include "CTimer.h"
#include "Patterns.h"

int &CTimer::m_snTimeInMillisecondsPauseMode = *reinterpret_cast<int *>(0x5F7614);
int &CTimer::m_snTimeInMilliseconds = *reinterpret_cast<int *>((0x885B48));
float &CTimer::ms_fTimeStepNonClipped = *reinterpret_cast<float *>((0x8E2C4C));
float &CTimer::ms_fTimeStep = *reinterpret_cast<float *>((0x8E2CB4));
int &CTimer::m_snPreviousTimeInMilliseconds = *reinterpret_cast<int *>((0x8F29E4));
float &CTimer::ms_fTimeScale = *reinterpret_cast<float *>((0x8F2C20));
int &CTimer::m_snTimeInMillisecondsNonClipped = *reinterpret_cast<int *>((0x9412E8));
unsigned int &CTimer::m_FrameCounter = *reinterpret_cast<unsigned int *>((0x9412EC));
bool &CTimer::m_UserPause = *reinterpret_cast<bool *>((0x95CD7C));
bool &CTimer::m_CodePause = *reinterpret_cast<bool *>((0x95CDB1));
int &suspendPcTimer = *reinterpret_cast<int *>((0x62A308));
int &suspendDepth = *reinterpret_cast<int *>((0x62A320));
int &oldPcTimer = *reinterpret_cast<int *>((0x9434F4));

static CPatch InjectPatches([]() {

});
