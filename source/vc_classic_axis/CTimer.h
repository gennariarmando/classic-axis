#pragma once

class CTimer {
public:
	static int &m_snTimeInMillisecondsPauseMode;
	static int &m_snTimeInMilliseconds;
	static float &ms_fTimeStepNonClipped;
	static float &ms_fTimeStep;
	static int &m_snPreviousTimeInMilliseconds;
	static float &ms_fTimeScale;
	static int &m_snTimeInMillisecondsNonClipped;
	static unsigned int &m_FrameCounter;
	static bool &m_UserPause;
	static bool &m_CodePause;
;
};

inline bool ShowFlashingItem(signed int nOnDuration, signed int nOffDuration) {
	return CTimer::m_snTimeInMillisecondsPauseMode % (nOnDuration + nOffDuration) < nOnDuration;
}

extern int &suspendPcTimer;
extern int &suspendDepth;
extern int &oldPcTimer;
