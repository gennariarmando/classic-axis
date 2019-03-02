#pragma once

#include "CStreamingInfo.h"
#include "CVector.h"
#include "eLevelName.h"
#include "CPtrList.h"
#include "CEntity.h"

class CDirectory;

class CStreaming {
public:
	// variables
	static unsigned int &ms_streamingBufferSize;
	static unsigned int &ms_numPriorityRequests;
	static unsigned int &ms_memoryUsed;
	static unsigned int &ms_memoryAvailable;
	static unsigned int &desiredNumVehiclesLoaded;
	static int &ms_channelError;
	static bool &ms_bLoadingBigModel;
	static bool &ms_disableStreaming;
	static int &ms_vehiclesLoaded;
	static unsigned int &ms_numVehiclesLoaded;
	static unsigned short &ms_loadedGangs;
	static int &ms_currentPedLoading;
	static int &ms_currentPedGrp;
	static bool &ms_hasLoadedLODs;
	static int &ms_oldSectorX;
	static int &ms_oldSectorY;
	static unsigned int &timeBeforeNextLoad;
	static unsigned int &ms_imageSize;
	static int &ms_imageOffsets;
	static int &ms_lastImageRead;
	static int &ms_lastVehicleDeleted;
	static unsigned int &ms_numModelsRequested;

	static CStreamingInfo *ms_startLoadedList;
	static CStreamingInfo *ms_startRequestedList;
	static CStreamingInfo *ms_endRequestedList;

	static CStreamingInfo *ms_aInfoForModel;

	static void *ms_pStreamingBuffer;
	static CDirectory **ms_pExtraObjectsDir;	
};
