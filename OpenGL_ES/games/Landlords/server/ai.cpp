#include "rules.h"

void sort_cards(PCard cards)
{
}

PHand get_greater_hand(PHand input)
{
	
}

HandType get_hand_type(PHand hand)
{
	if(hand->num_cards == 1) return SINGLE;
	else if(hand->num_cards == 2)
	{
		if( equal_single(&hand->cards[0],&hand->cards[1]) ) 
			return PAIR;//normal pair
		if(hand->cards[0].rank >= JOKER_BLACK_RANK && hand->cards[1].rank >= JOKER_BLACK_RANK)
			return ROCKET;//JOKER Pair
	}
	else if(hand->num_cards == 3)
	{
		if( equal_single(&hand->cards[0],&hand->cards[1]) && equal_single(&hand->cards[1],&hand->cards[2])) 
			return TRIPLE;//triple
	}
	else if(hand->num_cards == 4)
	{
		if( equal_single(&hand->cards[0],&hand->cards[1]) && equal_single(&hand->cards[1],&hand->cards[2])) 
			return TRIPLE_PLUS_SINGLE;//triple plus single
		if( equal_single(&hand->cards[0],&hand->cards[1]) && 
			equal_single(&hand->cards[1],&hand->cards[2]) && 
			equal_single(&hand->cards[2],&hand->cards[3]) ) 
			return BOMB;// bomb
	}
	return ILLEGAL;
}

bool is_hand_legal(PHand hand)
{
	sort_cards(hand->cards);
	return get_hand_type(hand) != ILLEGAL;
}