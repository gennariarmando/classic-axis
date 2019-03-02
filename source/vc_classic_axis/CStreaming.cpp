#include "CGTAVC.h"
#include "CStreaming.h"

unsigned int &CStreaming::ms_streamingBufferSize = *(unsigned int *)0x942FB0;
unsigned int &CStreaming::timeBeforeNextLoad = *(unsigned int *)0x6212F8;
bool &CStreaming::ms_bLoadingBigModel = *(bool *)0x95CDB0;
int &CStreaming::ms_channelError = *(int *)0x880DB8;
int &CStreaming::ms_currentPedGrp = *(int *)0x8F2BBC;
int &CStreaming::ms_currentPedLoading = *(int *)0x8F2C74;
bool &CStreaming::ms_disableStreaming = *(bool *)0x95CD6E;
bool &CStreaming::ms_hasLoadedLODs = *(bool *)0x95CD47;
int &CStreaming::ms_imageOffsets = *(int *)0x6E60A0;
unsigned int &CStreaming::ms_imageSize = *(unsigned int *)0x8F1A34;
int &CStreaming::ms_lastImageRead = *(int *)0x880E2C;
int &CStreaming::ms_lastVehicleDeleted = *(int *)0x95CBF8;
unsigned short &CStreaming::ms_loadedGangs = *(unsigned short *)0x95CC60;
unsigned int &CStreaming::ms_memoryAvailable = *(unsigned int *)0x880F8C;
unsigned int &CStreaming::ms_memoryUsed = *(unsigned int *)0x940568;
unsigned int &CStreaming::ms_numModelsRequested = *(unsigned int *)0x8E2C10;
unsigned int &CStreaming::ms_numPriorityRequests = *(unsigned int *)0x8F31C4;
unsigned int &CStreaming::ms_numVehiclesLoaded = *(unsigned int *)0x8F2C80;
int &CStreaming::ms_oldSectorX = *(int *)0x8F2C84;
int &CStreaming::ms_oldSectorY = *(int *)0x8F2C88;
int &CStreaming::ms_vehiclesLoaded = *(int *)0x773560;

CStreamingInfo *CStreaming::ms_aInfoForModel = (CStreamingInfo *)0x6C7088;
CStreamingInfo *CStreaming::ms_endRequestedList = (CStreamingInfo *)0x940738;
CStreamingInfo *CStreaming::ms_startLoadedList = (CStreamingInfo *)0x942F60;
CStreamingInfo *CStreaming::ms_startRequestedList = (CStreamingInfo *)0x8F1B3C;

void *CStreaming::ms_pStreamingBuffer = (void *)0x87F818;
CDirectory **CStreaming::ms_pExtraObjectsDir = (CDirectory **)0x95CB90;