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
	int rank;
	Suit suit;
} Card, *PCard;

typedef struct hand_t {
	Card cards[20];
	int num_cards;
} Hand, *PHand;

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



