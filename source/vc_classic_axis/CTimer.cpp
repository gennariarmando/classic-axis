#include "CGTAVC.h"
#include "CTimer.h"
#include "Patterns.h"

int &CTimer::m_snTimeInMillisecondsPauseMode = *reinterpret_cast<int *>(0x691014);
int &CTimer::m_snTimeInMilliseconds = *reinterpret_cast<int *>(0x974B2C);
float &CTimer::ms_fTimeStepNonClipped = *reinterpret_cast<float *>(0x9753A8);
float &CTimer::ms_fTimeStep = *reinterpret_cast<float *>(0x975424);
int &CTimer::m_snPreviousTimeInMilliseconds = *reinterpret_cast<int *>(0x978D8C);
float &CTimer::ms_fTimeScale = *reinterpret_cast<float *>(0x97F264);
int &CTimer::m_snTimeInMillisecondsNonClipped = *reinterpret_cast<int *>(0xA0D894);
unsigned int &CTimer::m_FrameCounter = *reinterpret_cast<unsigned int *>(0xA0D898);
bool &CTimer::m_UserPause = *reinterpret_cast<bool *>(0xA10B36);
bool &CTimer::m_CodePause = *reinterpret_cast<bool *>(0xA10B76);
int &suspendPcTimer = *reinterpret_cast<int *>(0x7052F8);
int &suspendDepth = *reinterpret_cast<int *>(0x705310);
int &oldPcTimer = *reinterpret_cast<int *>(0xA10680);
