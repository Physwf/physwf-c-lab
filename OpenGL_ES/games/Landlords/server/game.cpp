#include "game.h"
#include "services.h"
#include "ai.h"
#include <random.h>
#include <string.h>
#include <stdio.h>
#include <log/Log.h>

Game game;

void init()
{
	Log::info("init game!");
	for(int i=(int)SPADE;i<(int)DIAMOND;i++)
	{
		for(int j=0;j<13;j++)
		{
			game.pool[i*13+j].rank = j;
			game.pool[i*13+j].suit = (Suit)i;
		}
	}
	game.pool[52].rank = JOKER_BLACK_RANK;
	game.pool[53].rank = JOKER_RED_RANK;
	init_service();
}

void shuffle(int times)
{
	for(int i=0;i<times;i++)
	{
		int index1 = rand_by_range(0,NUM_CARDS-1);
		int index2 = rand_by_range(0,NUM_CARDS-1);
		PCard temp = game.pool+index1;
		game.pool[index1].rank = game.pool[index2].rank;
		game.pool[index1].suit = game.pool[index2].suit;
		game.pool[index2].rank = temp->rank;
		game.pool[index2].suit = temp->suit;
	}
}

void deal_cards()
{
	int cards_left = NUM_CARDS;
	while(cards_left>3)
	{
		for(int j=0;j<NUM_PLAYERS;j++)
		{
			PPlayer player = &game.players[j];
			player->cards[player->num_cards++] = game.pool[cards_left-1];
			cards_left--;
		}
	}
	PDealResult result = &game.dresult;
	for(int j=0;j<NUM_PLAYERS;j++)
	{
		PPlayer player = &game.players[j];
		result->playerIds[j] = player->id;
		for(int i=0;i<player->num_cards;i++)
		{
			result->cards[i] = player->cards[i];
		}
	}
	for(int j=0;j<3;j++)
	{
		result->loot[j] = game.pool[cards_left+j];
		cards_left --;
	}
}

void wait_for_loot()
{
	int loot_turn = game.loot_turn;
	if(loot_turn >= NUM_PLAYERS)
	{
		
		return;
	}
	if(game.players[loot_turn].isAI)
	{
		scores[loot_turn] = calculate_loot_score(&game.players[loot_turn]);
		broadcast_loot_score(game.players[loot_turn].id,scores[loot_turn]);
	}
	else
	{
		//send message
		//add listener
		SuspendThread(mainThread);
	}
	game.loot_turn++;
}

void start()
{
	// memset(players,0,sizeof(players));
	shuffle(10);
	deal_cards();
	send_deal_result(&game.dresult);
	
	wait_for_loot();
}

void turn()
{
	int next = game.landlord + (game.turn % NUM_PLAYERS);
	
	game.turn++;
}

void run()
{
	while(true)
	{
		turn();
		//game over?
	}
}