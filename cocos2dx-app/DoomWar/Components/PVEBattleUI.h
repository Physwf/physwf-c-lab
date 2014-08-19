#ifndef _PVEBATTLE_UI_H
#define _PVEBATTLE_UI_H

#include "cocos2d.h"
using namespace cocos2d;

class PVEUIController;

class PVEBattleUI : public CCSprite
{
public:
	static PVEBattleUI* create();

	virtual void onEnter();
	virtual void onExit();
private:
	PVEBattleUI();
	~PVEBattleUI();
private:
	CCSprite* mFrame;
	PVEUIController* mController;
};

/*PVEUIController*/
class PVEUIController : public CCTouchDelegate, public CCObject
{
public:
	PVEUIController(PVEBattleUI* view);
	~PVEUIController();

	static PVEUIController* create(PVEBattleUI* view);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
private:
	PVEBattleUI* mView;
};
#endif