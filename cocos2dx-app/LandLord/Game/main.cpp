#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <log/Log.h>

#include "game.h"
#include "../shared/common.h"

FILE* Log::mStream = NULL;

CRITICAL_SECTION CS;


int main()
{
	if(!InitializeCriticalSectionAndSpinCount(&CS,0x00000400) ) return -1;
		
	init();
	run();
	
	DeleteCriticalSection(&CS);
	return 0;
	
}