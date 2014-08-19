#include "PVEBattleScene.h"

CCScene* PVEBattleScene::scene() const
{
	return mScene;
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

	mPVEUI = PVEBattleUI::create();
	this->addChild(mPVEUI);
	return true;
}


PVEBattleScene* PVEBattleScene::create()
{
	PVEBattleScene* pBattle = new PVEBattleScene();
	if (pBattle && pBattle->init())
	{
		pBattle->autorelease();
		pBattle->setTouchEnabled(true);
		pBattle->mScene->addChild(pBattle);
		return pBattle;
	}
	return NULL;
}

PVEBattleScene::PVEBattleScene()
{
	mScene = CCScene::create();
}

PVEBattleScene::~PVEBattleScene()
{

}





