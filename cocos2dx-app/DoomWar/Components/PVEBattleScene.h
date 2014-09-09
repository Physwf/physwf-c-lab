#ifndef _PVE_BATTLE_SCENE_H
#define _PVE_BATTLE_SCENE_H

#include "cocos2d.h"
using namespace cocos2d;

#include "PVEBattleUI.h"
#include "Command.h"

class PVEBattleScene : public CCLayer
{
public:
	virtual bool init();
	CCScene* scene() const;
	static PVEBattleScene* create();
	virtual void update(float delta);
	void addCommand(Command* cmd);

	CCSprite* layerActor();
	CCSprite* layerEffect();

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
private:
	PVEBattleScene();
	~PVEBattleScene();
private:
	CCSprite* mTempMap;
	CCScene* mScene;
	PVEBattleUI* mPVEUI;

	CommandSequence* mMainThread;

	CCSprite* mLayerActor;
	CCSprite* mLayerEffect;
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