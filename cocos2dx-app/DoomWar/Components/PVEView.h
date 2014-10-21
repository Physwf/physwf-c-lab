#ifndef _PVE_MAP_H
#define _PVE_MAP_H

#include "cocos2d.h"
using namespace cocos2d;

#include "PVEUI.h"
#include "Command.h"

class PVEView : public CCLayer
{
public:
	virtual bool init();
	CCScene* scene() const;
	static PVEView* create();
	virtual void update(float delta);
	void addCommand(Command* cmd);

	CCSprite* layerMap();
	CCSprite* layerProp();
	CCSprite* layerActor();
	CCSprite* layerEffect();
	PVEUI* ui();

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);

	void scroll(int dx, int dy);
private:
	PVEView();
	~PVEView();
private:
	CCSprite* mTempMap;
	CCScene* mScene;

	CommandSequence* mMainThread;

	CCSprite* mLayerMap;
	CCSprite* mLayerProp;
	CCSprite* mLayerActor;
	CCSprite* mLayerEffect;
	PVEUI* mUI;

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