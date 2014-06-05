
PHand get_greater_hand(PHand input)
{
	
}

HandType get_hand_type(PHand hand)
{
	if(hand->num_cards == 1) return SINGLE;
}

bool is_hand_legal(PHand hand)
{
	if(hand->num_cards == 1) return true;
	else if(hand->num_cards == 2)
	{
		if(hand->cards[0] == hand->cards[1]) return true;
		if(hand->cards[0] > )
	}
}