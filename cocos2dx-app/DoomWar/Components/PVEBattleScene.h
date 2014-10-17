#ifndef _PVE_MAP_H
#define _PVE_MAP_H

#include "cocos2d.h"
using namespace cocos2d;

#include "PVEBattleUI.h"
#include "Command.h"

class PVEMap : public CCLayer
{
public:
	virtual bool init();
	CCScene* scene() const;
	static PVEMap* create();
	virtual void update(float delta);
	void addCommand(Command* cmd);

	CCSprite* layerProp();
	CCSprite* layerActor();
	CCSprite* layerEffect();

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
private:
	PVEMap();
	~PVEMap();
private:
	CCSprite* mTempMap;
	CCScene* mScene;
	PVEBattleUI* mPVEUI;

	CommandSequence* mMainThread;

	CCSprite* mLayerProp;
	CCSprite* mLayerActor;
	CCSprite* mLayerEffect;
	ColorSprite* mRangeSprite;
	Actor* mCurDrag;
};

class TopTouchLayer : public CCLayer
{
public:
	static TopTouchLayer* create();

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
private:

};
#endif