#include "rules.h"

bool equal_single(PCard left, PCard right)
{
	return left->rank == right->rank;
}

bool greater_single(PCard card1,PCard card2)
{
	int rank1 = card1->rank;
	int rank2 = card2->rank;
	if(rank1 < 3) rank1 += 13;
	if(rank2 < 3) rank2 += 13;
	if(rank1 > 13) rank1 += 2;
	if(rank2 > 13) rank2 += 2;
	return rank1 > rank2;
}

bool greater_multiple(PCard cards1,PCard cards2)
{
	Card card1 = cards1[0];
	Card card2 = cards2[0];
	return greater_single(&card1,&card2);
}

bool greater_sequence(PCard cards1,PCard cards2)
{
	return false;
}

int get_rank(PCard card)
{
	return 0;
}