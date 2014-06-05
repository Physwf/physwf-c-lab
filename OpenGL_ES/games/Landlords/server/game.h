

#define NUM_CARDS 54
#define NUM_PLAYERS 3

#define JOKER_BLACK 14
#define JOKER_RED 15

typedef struct player_t {
	int cards[20];
	int num_cards;
	int turn;
	bool isLord;
	bool isAI;
} Player,*PPlayer;