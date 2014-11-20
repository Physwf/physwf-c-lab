#include "game.h"
#include <log/Log.h>
#include "../shared/common.h"

FILE* Log::mStream = NULL;
CRITICAL_SECTION CS;
HANDLE mainThread;

int main()
{
	if(!InitializeCriticalSectionAndSpinCount(&CS,0x00000400) )
		return -1;
	Log::init("LLserver.log");
	mainThread = GetCurrentThread();
	init();
	run();
	DeleteCriticalSection(&CS);
	return 0;
}