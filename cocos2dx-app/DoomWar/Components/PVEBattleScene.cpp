#include "PVEBattleScene.h"
#include "MapSprite.h"
#include "Engine.h"
#include "System.h"

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

	mPVEUI = PVEBattleUI::create(this);
	//TouchGroup * ul = TouchGroup::create();
	//ul->addWidget(GUIReader::shareReader()->widgetFromJsonFile("./Data/UIPVE_1/UIPVE_1.ExportJson"));
	//mScene->addChild(mPVEUI);
	mPVEUI->setTouchEnabled(true);
	//ul->setPosition(ccp(0, 0));
	mMainThread = CommandSequence::create();

	mRangeSprite = ColorSprite::create(0x6F0000FF);
	mRangeSprite->retain();
	mRangeSprite->setVisible(false);
	mLayerEffect->addChild(mRangeSprite);
	scheduleUpdate();

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

void PVEBattleScene::onEnter()
{
	CCLayer::onEnter();
}

void PVEBattleScene::onExit()
{
	CCLayer::onExit();
}

bool PVEBattleScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLog("x:%f,y:%f\n", touch->getLocation().x, touch->getLocation().y);
	mCurDrag = Engine::scene->getActorByGrid(touch->getLocation()-getPosition());
	if (mCurDrag != NULL)
	{
		mRangeSprite->updateData(mCurDrag->getData());
		const Position pos = mCurDrag->getData()->positon;
		mRangeSprite->setPosition(mCurDrag->sprite()->getPosition());
		mRangeSprite->setVisible(true);
	}
	else
	{
		mRangeSprite->setVisible(false);
	}
	return true;
}

void PVEBattleScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if (mCurDrag && mCurDrag->isHero())
	{
		mCurDrag->sprite()->setPosition(touch->getLocation() - getPosition());
		mRangeSprite->setPosition(touch->getLocation() - getPosition());
	}
}

void PVEBattleScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if (mCurDrag && mCurDrag->isHero())
	{

		int x = floor((touch->getLocation().x - getPositionX()- X_MARGIN) / GRID_SIZE);
		int y = floor((touch->getLocation().y - getPositionY()) / GRID_SIZE);
		mRangeSprite->setPosition(ccp(x * GRID_SIZE + X_MARGIN + GRID_SIZE / 2, y * GRID_SIZE + GRID_SIZE / 2));
		System::pve->moveHero(mCurDrag->getData()->iid, x, y);
	}
}

void PVEBattleScene::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{

}