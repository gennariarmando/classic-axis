#include "CGTAVC.h"
#include "CAutomobile.h"

bool &CAutomobile::m_sAllTaxiLights = *(bool *)0xA10ABB;
unsigned int &CAutomobile::nGenerateRaindrops = *(unsigned int *)0x77F754;
unsigned int &CAutomobile::nGenerateWaterCircles = *(unsigned int *)0x77F75C;
CMatrix *CAutomobile::matW2B = (CMatrix *)0x77F7D0;