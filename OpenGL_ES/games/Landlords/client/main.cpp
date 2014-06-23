#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <log/Log.h>

#include "net.h"
#include "listener.h"
#include "../shared/msg.h"

FILE* Log::mStream = NULL;

CRITICAL_SECTION CS;

void onDealResult(char* data)
{
	DealResult result;
	memcpy(&result,data,sizeof(DealResult));
	Log::info("onDealResult");
}

void init()
{
	Log::init("LLclient.log");
	if(!InitializeCriticalSectionAndSpinCount(&CS,0x00000400) )
		return;
	net_init();
	addMsgListener(MSG_NOTI_DEAL_RESULT_1000,onDealResult);
	DeleteCriticalSection(&CS);
}

int main()
{
	init();
	while(true)
	{
		listener_loop();
		Sleep(10);
	}
	return 0;
}