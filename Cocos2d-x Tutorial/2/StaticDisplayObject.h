#include "cocos2d.h"

class StaticDisplayObject : public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene * scene();

	void mouseCloseCallBack(CCObject * pSpender);

	CREATE_FUNC(StaticDisplayObject);
};