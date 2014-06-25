#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <log/Log.h>

#include "game.h"
#include "net.h"
#include "listener.h"
#include "../shared/msg.h"

void onDealResult(char* data)
{
	DealResult result;
	memcpy(&result,data,sizeof(DealResult));
	Log::info("onDealResult");
	printf("cards:\n");
	for(int i=0;i<17;i++)
	{
		printf("%d,",result.cards[i].rank);
	}
	printf("\n");
	printf("loot:\n");
	for(int i=0;i<3;i++)
	{
		printf("%d,",result.odd[i].rank);
	}
	printf("\n");
}

void init()
{
	char fname[30];
	sprintf(fname,"LLclient%8d.log",(int)time(NULL));
	
	Log::init(fname);
	net_init();
	addMsgListener(MSG_NOTI_DEAL_RESULT_1000,onDealResult);
}

void run()
{
	while(true)
	{
		listener_loop();
		Sleep(10);
	}
}