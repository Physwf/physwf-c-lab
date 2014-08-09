#include "PVEBattleScene.h"

CCScene* PVEBattleScene::scene()
{
	CCScene* scene = CCScene::create();
	PVEBattleScene* layer = PVEBattleScene::create();
	scene->addChild(layer);
	return scene;
}

bool PVEBattleScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
}





