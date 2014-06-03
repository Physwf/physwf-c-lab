#include "rules.h"

bool greater_single(int card1,int card2)
{
	int value1 = card1 & VALUE_BITS;
	int value2 = card2 & VALUE_BITS;
	if(value1 < 3) value1 += 13;
	if(value2 < 3) value2 += 13;
	if(value1 > 13) value1 += 2;
	if(value2 > 13) value2 += 2;
	return value1 > value2;
}

bool greater_multiple(int* cards1,int* cards2)
{
	int card1 = cards1[0];
	int card2 = cards2[0];
	return greater_single(card1,card2);
}

bool greater_sequence(int* cards1,int* cards2)
{
	
}