#include "rules.h"

bool equal_single(PCard left, PCard right)
{
	return left->rank == right->rank;
}

bool greater_single(PCard card1,PCard card2)
{
	int value1 = card1 & VALUE_BITS;
	int value2 = card2 & VALUE_BITS;
	if(value1 < 3) value1 += 13;
	if(value2 < 3) value2 += 13;
	if(value1 > 13) value1 += 2;
	if(value2 > 13) value2 += 2;
	return value1 > value2;
}

bool greater_multiple(PCard cards1,PCard cards2)
{
	int card1 = cards1[0];
	int card2 = cards2[0];
	return greater_single(card1,card2);
}

bool greater_sequence(PCard cards1,PCard cards2)
{
	
}

int get_rank(PCard card)
{
	
}