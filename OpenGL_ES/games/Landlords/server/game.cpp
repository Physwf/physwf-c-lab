#include "game.h"
#include "rules.h"
#include <random.h>

int pool[NUM_CARDS];
int turn;
player_t players[NUM_PLAYERS];

void init()
{
	const int suit[4] = SUIT;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<13;j++)
		{
			pool[i*13+j] = j+1 | suit[i];
		}
	}
	pool[52] = JOKER_BLACK;
	pool[53] = JOKER_RED;
}

void shuffle(int times)
{
	for(int i=0;i<times;i++)
	{
		int index1 = rand_by_range(0,NUM_CARDS-1);
		int index2 = rand_by_range(0,NUM_CARDS-1);
		int temp = pool[index1];
		pool[index1] = pool[index2];
		pool[index2] = temp;
	}
}

void start()
{
	memset(players,0,sizeof(players));
}

void run()
{
	while(true)
	{
		step();
		//game over?
	}
}

void step()
{
	
}
