#include "cocos2d.h"
#include "../shared/logic.h"
#include "Properties.h"

class PokerCardSprite :public cocos2d::CCSprite
{
public:
	PokerCardSprite(int rank, Suit suit);
	~PokerCardSprite();

	static PokerCardSprite* create(int rank, Suit suit);

private:
	cocos2d::CCSprite mFrontBg;
	cocos2d::CCSprite mBackBg;
	cocos2d::CCSprite mRankSprite;
	cocos2d::CCSprite mSmallSuitSprite;
	cocos2d::CCSprite mBigSuitSprite;

	Properties* mProperties;
};