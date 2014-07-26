#include "PokerCardSprite.h"

PokerCardSprite::PokerCardSprite(int rank, Suit suit)
{
	mProperties = new Properties(300);
	mProperties->readFile("./data/cards.properties");
	cocos2d::CCRect* rect = mProperties->getRect("spades.holder.play.sub.rect");
}

PokerCardSprite::~PokerCardSprite()
{

}


PokerCardSprite* PokerCardSprite::create(int rank, Suit suit)
{

	return NULL;
}