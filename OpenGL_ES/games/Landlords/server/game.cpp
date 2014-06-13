#include "game.h"
#include "services.h"
#include "ai.h"
#include <random.h>
#include <string.h>
#include <stdio.h>
#include <log/Log.h>

Card pool[NUM_CARDS];
int loot_turn;
int turn;
Player players[NUM_PLAYERS];

void init()
{
	Log::info("init game!");
	for(int i=(int)SPADE;i<(int)DIAMOND;i++)
	{
		for(int j=0;j<13;j++)
		{
			pool[i*13+j].rank = j;
			pool[i*13+j].suit = (Suit)i;
		}
	}
	pool[52].rank = JOKER_BLACK_RANK;
	pool[53].rank = JOKER_RED_RANK;
	init_service();
}

void shuffle(int times)
{
	for(int i=0;i<times;i++)
	{
		int index1 = rand_by_range(0,NUM_CARDS-1);
		int index2 = rand_by_range(0,NUM_CARDS-1);
		PCard temp = pool+index1;
		pool[index1].rank = pool[index2].rank;
		pool[index1].suit = pool[index2].suit;
		pool[index2].rank = temp->rank;
		pool[index2].suit = temp->suit;
	}
}

void deal_cards()
{
	for(int i=0;i<NUM_CARDS;i++)
	{
		for(int j=0;j<NUM_PLAYERS;j++)
		{
			PPlayer player = &players[j];
			player->cards[player->num_cards++] = pool[i];
		}
	}
}

void wait_for_loot()
{
	int scores[3];
	for(int i=0;i<NUM_PLAYERS;i++)
	{
		if(players[i].isAI)
		{
			scores[i] = calculate_loot_score(&players[i]);
			//send message
		}
		else
		{
			//send message
		}
	}
}

void start()
{
	memset(players,0,sizeof(players));
	shuffle(10);
	deal_cards();
	//wait for loot
	wait_for_loot();
}

void step()
{
	
}

void run()
{
	while(true)
	{
		step();
		//game over?
	}
}