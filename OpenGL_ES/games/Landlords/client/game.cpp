#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <log/Log.h>

#include "game.h"
#include "net.h"
#include "listener.h"
#include "../shared/msg.h"

void onAskWaitMore(char* data)
{
	printf("Wait for Player(s):\n");
	printf("You can wait for more players, or start the game immediately!\n");
}

void onPlayerJoin(char* data)
{
	printf("Player joined!\n");
}

void onHostWaitMorePlayers(char* data)
{
	printf("Host are waiting for more players!\n");
}

void onDealResult(char* data)
{
	MSG_NOTI_DEAL_RESULT msg;
	memcpy(&msg,data,sizeof(MSG_NOTI_DEAL_RESULT));
	Log::info("onDealResult");
	printf("cards:\n");
	for(int i=0;i<17;i++)
	{
		printf("%d,",msg.result.cards[i].rank);
	}
	printf("\n");
	printf("loot:\n");
	for(int i=0;i<3;i++)
	{
		printf("%d,",msg.result.odd[i].rank);
	}
	printf("\n");
}

void init()
{
	char fname[30];
	sprintf(fname,"LLclient%8d.log",(int)time(NULL));
	
	Log::init(fname);
	net_init();
	
	addMsgListener(MSG_NOTI_ASK_WAIT_MORE_1000,onAskWaitMore);
	addMsgListener(MSG_NOTI_PLAYER_JOIN_1001,onPlayerJoin);
	addMsgListener(MSG_NOTI_HOST_WAIT_PLAYERS_1002,onHostWaitMorePlayers);
	addMsgListener(MSG_NOTI_DEAL_RESULT_1004,onDealResult);
}

void run()
{
	while(true)
	{
		listener_loop();
		Sleep(10);
	}
}