#include <stdio.h>

#include <log/Log.h>

#include "LLLog.h"
#include "game.h"

void LL_log_pool()
{
	Log::info("pool:");
	char buffer[200];
	for(int i=0;i<NUM_CARDS;i++)
	{
		Log::info("%d,",game.pool[i].rank);
	}
}

void LL_log_player_cards()
{
	for(int i=0;i<NUM_PLAYERS;i++)
	{
		Log::info("player %d cards:",i);
		for(int j=0;j<17;j++)
		{
			Log::info("%d,",game.players[i].cards[j].rank);
		}
	}
}

void LL_log_deal_result()
{
	for(int i=0;i<NUM_PLAYERS;i++)
	{
		Log::info("player %d deal result:",i);
		for(int j=0;j<17;j++)
		{
			Log::info("%d,",game.dresults[i].cards[j].rank);
		}
	}
	Log::info("odd:");
	for(int i=0;i<3;i++)
	{
		Log::info("%d,",game.dresults[0].odd[i].rank);
	}
}