#ifndef _PVEBATTLE_UI_H
#define _PVEBATTLE_UI_H

#include "cocos2d.h"
#include "cocos-ext.h"
#include "PVEBattleScene.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace ui;

class PVEUIController;

class PVEBattleUI : public TouchGroup
{
public:
	static PVEBattleUI* create(PVEBattleScene* pve);

	virtual void onEnter();
	virtual void onExit();
private:
	PVEBattleUI();
	~PVEBattleUI();

	void onLeftTouched(CCObject* object, TouchEventType type);
	void onForwardTouched(CCObject* object, TouchEventType type);
	void onBackwardTouched(CCObject* object, TouchEventType type);
	void onRightwardTouched(CCObject* object, TouchEventType type);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
private:
	CCSprite* mFrame;
	PVEBattleScene* mPVEBattle;
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