#include "CGTA3D.h"
#include "CAutomobile.h"

bool &CAutomobile::m_sAllTaxiLights = *(bool *)0x95CD21;
unsigned int &CAutomobile::nGenerateRaindrops = *(unsigned int *)0x64CDEC;
unsigned int &CAutomobile::nGenerateWaterCircles = *(unsigned int *)0x64CDF4;
CMatrix *CAutomobile::matW2B = (CMatrix *)0x64CE54;