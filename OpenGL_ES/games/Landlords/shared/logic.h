#ifndef _LOGIC_H
#define _LOGIC_H

#include "connection.h"

#define JOKER_BLACK_RANK 14
#define JOKER_RED_RANK 15

#define NUM_CARDS 54
#define NUM_PLAYERS 3

typedef enum {
	SPADE,
	HEART,
	CLUB,
	DIAMOND
} Suit;

typedef struct card_t {
	unsigned short rank;
	Suit suit;
} Card, *PCard;

typedef enum {
	SINGLE,
	PAIR,
	TRIPLE,
	BOMB,
	TRIPLE_PLUS_SINGLE,
	TRIPLE_PLUS_PAIR,
	ROCKET,
	SINGLE_SEQUENCE,
	PAIR_SEQUENCE,
	TRIPLE_SEQUENCE,
	TRIPLE_SEQUENCE_PLUS_SINGLE,
	TRIPLE_SEQUENCE_PLUS_PAIR,
	ILLEGAL
} HandType;

typedef struct hand_t {
	Card cards[20];
	int num_cards;
	HandType type;
} Hand, *PHand;

bool equal_single(PCard left, PCard right);
bool greater_single(PCard card1,PCard card2);
bool greater_multiple(PCard cards1,PCard cards2);
bool greater_sequence(PCard cards1,PCard cards2);

typedef struct player_t {
	int id;
	PConnection connection;
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
	bool isHost;
} Player,*PPlayer;

typedef struct deal_result_t {
	Card cards[17];
	Card odd[3];
} DealResult, *PDealResult;

typedef struct game_t {
	Card pool[NUM_CARDS];
	Player players[NUM_PLAYERS];
	int num_players;
	int loot_turn;
	int loot_scores[NUM_PLAYERS];
	int turn;
	DealResult dresults[NUM_PLAYERS];
	int landlord;//players index
	int phase;
	Hand cur_hand;
} Game, *PGame;

#endif