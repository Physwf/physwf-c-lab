#include "PokerCardSprite.h"
#include "jpstring.h"

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
		//side suit rect
		cocos2d::CCRect* sRect;
		sRect = pSprite->mProperties->getRect("spades.card.suit.rect");
		sRect->origin.x = sRect->size.width * (3-(int)suit);
		pSprite->mSideSuitSprite = cocos2d::CCSprite::create("./data/card-pieces.png",*sRect);
		pSprite->mSideSuitSprite->setAnchorPoint(ccp(0,0));
		cocos2d::CCPoint* sPos;
		sPos = pSprite->mProperties->getPoint("spades.card.suit.pt");
		pSprite->mSideSuitSprite->setPosition(ccp(sPos->x - bRect->size.width / 2, sPos->y - bRect->size.height/2));
		pSprite->addChild(pSprite->mSideSuitSprite);

		char value[512];
		int len = pSprite->mProperties->getProperty("spades.card.s1 ", value);
		char* parts[4];
		int listlen = jpsplit(value, ",", parts);
		jptrim(parts[3]);
		char* subkeys[20];
		int list2len = jpsplit(parts[3], ":", subkeys);
		char* rectkey = subkeys[0];
		int index = atoi(&rectkey[strlen(rectkey) - 1]);
		return pSprite;
	}
	return NULL;
}