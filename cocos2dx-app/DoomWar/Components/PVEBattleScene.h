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
#endif