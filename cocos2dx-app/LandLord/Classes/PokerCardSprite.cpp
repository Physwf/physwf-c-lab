#include "PokerCardSprite.h"

PokerCardSprite::PokerCardSprite(int rank, Suit suit)
{
	mProperties = new Properties(50);
	mProperties->readFile("./data/cards.properties");
}

PokerCardSprite::~PokerCardSprite()
{

}


PokerCardSprite* PokerCardSprite::create(int rank, Suit suit)
{

	return NULL;
}