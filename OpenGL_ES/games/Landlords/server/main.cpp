#include "game.h"
#include <log/Log.h>
#include "../shared/common.h"

FILE* Log::mStream = NULL;
CRITICAL_SECTION CS;

int main()
{
	if(!InitializeCriticalSectionAndSpinCount(&CS,0x00000400) )
		return -1;
	Log::init("LLserver.log");
	init();
	DeleteCriticalSection(&CS);
	return 0;
}