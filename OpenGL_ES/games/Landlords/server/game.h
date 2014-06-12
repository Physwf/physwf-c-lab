#ifndef _GAME_H
#define _GAME_H

#include "rules.h"

typedef struct player_t {
	int playerID;
	Card cards[20];
	int num_cards;
	int singles[20];
	int num_singles;
	int pairs[20];
	int num_pairs;
	int triples[20];
	int num_triples;
	int bombs[20];
	int num_bombs;
	int turn;
	bool isLord;
	bool isAI;
} Player,*PPlayer;

void init();

#endif