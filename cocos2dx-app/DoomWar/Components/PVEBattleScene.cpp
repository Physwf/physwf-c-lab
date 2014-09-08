#include "PVEBattleScene.h"
#include "MapSprite.h"

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
	
	mTempMap = MapSprite::create(0);
	mTempMap->setPosition(ccp(-64, 0));
	this->addChild(mTempMap);
	//CCTMXTiledMap::create();

	mLayerActor = CCSprite::create();
	mLayerEffect = CCSprite::create();
	this->addChild(mLayerActor);
	this->addChild(mLayerEffect);

	mPVEUI = PVEBattleUI::create();
	//TouchGroup * ul = TouchGroup::create();
	//ul->addWidget(GUIReader::shareReader()->widgetFromJsonFile("./Data/UIPVE_1/UIPVE_1.ExportJson"));
	//mScene->addChild(mPVEUI);
	mPVEUI->setTouchEnabled(true);
	//ul->setPosition(ccp(0, 0));
	mMainThread = CommandSequence::create();

	scheduleUpdate();

	return true;
}


PVEBattleScene* PVEBattleScene::create()
{
	PVEBattleScene* pBattle = new PVEBattleScene();
	if (pBattle && pBattle->init())
	{
		pBattle->autorelease();
		//pBattle->setTouchEnabled(true);
		pBattle->mScene->addChild(pBattle);
		pBattle->mScene->addChild(pBattle->mPVEUI);
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

void PVEBattleScene::update(float delta)
{
	mMainThread->tick(delta);
}

void PVEBattleScene::addCommand(Command* cmd)
{
	mMainThread->push(cmd);
}

CCSprite* PVEBattleScene::layerActor()
{
	return mLayerActor;
}

CCSprite* PVEBattleScene::layerEffect()
{
	return mLayerEffect;
}


