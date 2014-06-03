#include "tabble.h"
#include <random.h>

int pool[NUM_CARDS];
int turn_counters[NUM_PLAERS];
int cur_player = 0;

void init()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<13;j++)
		{
			pool[i*13+j] = j+1;
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