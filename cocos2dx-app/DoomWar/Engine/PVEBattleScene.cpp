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
	
	mTempMap = CCSprite::create("./Data/map.png");
	mTempMap->setAnchorPoint(ccp(0, 0));
	this->addChild(mTempMap);
	//CCTMXTiledMap::create();
	return true;
}


PVEBattleScene* PVEBattleScene::create()
{
	PVEBattleScene* pBattle = new PVEBattleScene();
	if (pBattle && pBattle->init())
	{
		pBattle->autorelease();
		return pBattle;
	}
	return NULL;
}




