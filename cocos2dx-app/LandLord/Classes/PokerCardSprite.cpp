#include "PokerCardSprite.h"

PokerCardSprite::PokerCardSprite(int rank, Suit suit)
{
	mProperties = new Properties(300);
	mProperties->readFile("./data/cards.properties");
}

PokerCardSprite::~PokerCardSprite()
{

}


PokerCardSprite* PokerCardSprite::create(int rank, Suit suit)
{
	if (!(rank > 0 && rank < 16)) return NULL;
	PokerCardSprite * pSprite = new PokerCardSprite(rank,suit);
	if (pSprite && pSprite->init())
	{
		pSprite->autorelease();
		cocos2d::CCRect* bRect = pSprite->mProperties->getRect("spades.holder.cardhilite.sub.rect");
		pSprite->mFrontBg = cocos2d::CCSprite::create("./data/cards.png", *bRect);
		pSprite->addChild(pSprite->mFrontBg);
		//value rect
		cocos2d::CCRect* vRect;
		if (suit == SPADE || suit == DIAMOND)
			vRect = pSprite->mProperties->getRect("spades.card.bval.rect");
		else if(suit == HEART || suit == CLUB)
			vRect = pSprite->mProperties->getRect("spades.card.rval.rect");
		vRect->origin.x = vRect->size.width * (rank-1);
		pSprite->mRankSprite = cocos2d::CCSprite::create("./data/card-pieces.png",*vRect);
		pSprite->addChild(pSprite->mRankSprite);
		cocos2d::CCPoint* rPos = pSprite->mProperties->getPoint("spades.card.val.pt");
		pSprite->mRankSprite->setPosition(ccp(rPos->x + vRect->size.width /2 - bRect->size.width / 2, rPos->y + bRect->size.height / 2 - vRect->size.height));
		return pSprite;
	}
	return NULL;
}