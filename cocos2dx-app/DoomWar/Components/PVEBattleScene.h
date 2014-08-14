#ifndef _PVE_BATTLE_SCENE_H
#define _PVE_BATTLE_SCENE_H

#include "cocos2d.h"
using namespace cocos2d;

class PVEBattleScene : public CCLayer
{
public:
	virtual bool init();
	static CCScene* scene();
	static PVEBattleScene* create();
private:
	CCSprite* mTempMap;
};
#endif