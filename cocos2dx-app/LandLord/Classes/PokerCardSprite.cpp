#include "PokerCardSprite.h"
#include "jpstring.h"
#include "Config.h"

PokerCardSprite::PokerCardSprite(int rank, Suit suit)
{
	mProperties = Config::getInstance()->getProperties();
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
		pSprite->mSideSuitSprite->setPosition(ccp(sPos->x - bRect->size.width / 2, -sPos->y + bRect->size.height/2 - sRect->size.height));
		pSprite->addChild(pSprite->mSideSuitSprite);

		char value[512] = { 0 };
		char pkey[50];
		switch(suit)
		{
			case SPADE:
				sprintf(pkey, "spades.card.s%d", rank);
				break;
			case HEART:
				sprintf(pkey, "spades.card.h%d", rank);
				break;
			case CLUB:
				sprintf(pkey, "spades.card.c%d", rank);
				break;
			case DIAMOND:
				sprintf(pkey, "spades.card.d%d", rank);
				break;
		}
		int len = pSprite->mProperties->getProperty(pkey, value);
		char* parts[4] = {0};
		int listlen = jpsplit(value, ",", parts);
		parts[3] = jptrim(parts[3]);
		char* subkeys[20] = {0};
		int partslen = jpsplit(parts[3], ":", subkeys);
		char* rectkey = subkeys[0];
		int index = atoi(&rectkey[strlen(rectkey) - 2]);
		rectkey[strlen(rectkey) - 3] = 0;
		char** ptkeys = &subkeys[1];
		int ptnum = partslen - 1;
		char fullrectkey[25] = { 0 };
		sprintf(fullrectkey, "spades.card.%s.rect", rectkey);
		cocos2d::CCRect* pipRect = pSprite->mProperties->getRect(fullrectkey);
		pipRect->origin.x += pipRect->size.width * index;
		cocos2d::CCPoint * pippt;
		char fullptkey[25] = {0};
		cocos2d::CCSprite* pipSprite;
		for (int i = 0; i < ptnum; i++)
		{
			char* ptkey = ptkeys[i];
			char keylen = strlen(ptkey);
			sprintf(fullptkey, "spades.card.%s.pt", ptkey);
			pippt = pSprite->mProperties->getPoint(fullptkey);
			pipSprite = cocos2d::CCSprite::create("./data/card-pieces.png", *pipRect);
			pipSprite->setPosition(ccp(pippt->x - bRect->size.width / 2, pippt->y - bRect->size.height / 2));
			pipSprite->setAnchorPoint(ccp(0,0));
			pSprite->addChild(pipSprite);
		}

		bRect->origin.x += bRect->size.width;
		pSprite->mBackBg = cocos2d::CCSprite::create("./data/cards.png", *bRect);
		pSprite->addChild(pSprite->mBackBg);
		pSprite->mBackBg->setVisible(false);
		return pSprite;
	}
	return NULL;
};

void PokerCardSprite::reverse()
{
	mBackBg->setVisible(true);
};

void PokerCardSprite::obverse()
{
	mBackBg->setVisible(false);
};

void PokerCardSprite::rotate(float angle)
{
	this->setRotation(angle);
}