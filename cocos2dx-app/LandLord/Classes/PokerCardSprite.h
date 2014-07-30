#include "cocos2d.h"
#include "../shared/logic.h"
#include "Properties.h"

class PokerCardSprite :public cocos2d::CCSprite
{
public:
	PokerCardSprite(int rank, Suit suit);
	~PokerCardSprite();
	void reverse();
	void obverse();
	void rotate(float angle);
	static PokerCardSprite* create(int rank, Suit suit);

private:
	cocos2d::CCSprite *mFrontBg;
	cocos2d::CCSprite *mBackBg;
	cocos2d::CCSprite *mRankSprite;
	cocos2d::CCSprite *mSideSuitSprite;
	cocos2d::CCSprite *mCenterSuitSprite;

	Properties* mProperties;
};