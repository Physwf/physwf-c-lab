#ifndef _PVE_BATTLE_SCENE_H
#define _PVE_BATTLE_SCENE_H

#include "cocos2d.h"
using namespace cocos2d;

#include "PVEBattleUI.h"

class PVEBattleScene : public CCLayer
{
public:
	
	virtual bool init();
	CCScene* scene() const;
	static PVEBattleScene* create();
private:
	PVEBattleScene();
	~PVEBattleScene();
private:
	CCSprite* mTempMap;
	CCScene* mScene;
	PVEBattleUI* mPVEUI;
};
#endif