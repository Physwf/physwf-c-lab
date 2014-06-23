#include "sort.h"

void swap(PCard card1, PCard card2)
{
	Card temp = *card1;
	*card1 = *card2;
	*card2 = temp;
}

int partion(PCard cards, int low, int high)
{
	Card p = cards[high-1];
	int i = low;
	int j = low + 1;
	for(;j<high;j++)
		if(greater_single(&cards[j],&p))
		{
			i++;
			swap(&cards[i],&cards[j]);
			// Card temp = cards[i];
			// cards[i] = cards[j];
			// cards[j] = temp;
		}
	swap(&cards[i],&cards[high-1]);
	return i;
}

void q_sort(PCard cards, int low, int high)
{
	if(low < high)
	{
		int q = partion(cards,low,high);
		q_sort(cards,low,q-1);
		q_sort(cards,q+1,high);
	}
}