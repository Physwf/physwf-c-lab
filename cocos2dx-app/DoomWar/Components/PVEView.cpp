#include "PVEView.h"
#include "Engine.h"
#include "System.h"
#include <stdio.h>

CCScene* PVEView::scene() const
{
	return mScene;
}

bool PVEView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
		
	mLayerMap = CCSprite::create();
	mLayerProp = CCSprite::create();
	mLayerActor = CCSprite::create();
	mLayerEffect = CCSprite::create();
	mUI = PVEUI::create(this);
	mUI->setTouchEnabled(true);

	this->addChild(mLayerMap);
	this->addChild(mLayerProp);
	this->addChild(mLayerActor);
	this->addChild(mLayerEffect);
	this->addChild(mUI);

	CCTMXTiledMap* map = CCTMXTiledMap::create("./Data/MAPPVE.tmx");
	map->setPosition(-65, 0);
	mLayerMap->addChild(map);

	mMainThread = CommandSequence::create();

	mRangeSprite = ColorSprite::create(0x6F0000FF);
	mRangeSprite->retain();
	mRangeSprite->setVisible(false);
	mLayerEffect->addChild(mRangeSprite);
	scheduleUpdate();

	return true;
}


PVEView* PVEView::create()
{
	PVEView* pBattle = new PVEView();
	if (pBattle && pBattle->init())
	{
		pBattle->autorelease();
		pBattle->setTouchEnabled(true);
		return pBattle;
	}
	return NULL;
}

PVEView::PVEView()
{
	mScene = CCScene::create();
}

PVEView::~PVEView()
{

}

void PVEView::update(float delta)
{
	mMainThread->tick(delta);
}

void PVEView::addCommand(Command* cmd)
{
	mMainThread->push(cmd,true);
}

CCSprite* PVEView::layerMap()
{
	return mLayerMap;
}

CCSprite* PVEView::layerProp()
{
	return mLayerProp;
}

CCSprite* PVEView::layerActor()
{
	return mLayerActor;
}

CCSprite* PVEView::layerEffect()
{
	return mLayerEffect;
}

PVEUI* PVEView::ui()
{
	return mUI;
}

void PVEView::updateGold(int gold)
{
	char sGold[8] = { 0 };
	sprintf(sGold, "%d", gold);
	mUI->labelGold()->setText(sGold);
}

void PVEView::updateStep(int step)
{
	char sStep[8] = { 0 };
	sprintf(sStep, "%d", step);
	mUI->labelStep()->setText(sStep);
}

void PVEView::showSumary()
{
	mUI->panelSumary()->setScale(0.5);
	mUI->addWidget(mUI->panelSumary());
	mUI->setStarLevel(2);
	CCScaleTo* scale = CCScaleTo::create(0.1, 1.0);
	mUI->panelSumary()->runAction(CCEaseIn::create(scale,0.1));
}

void PVEView::onEnter()
{
	CCLayer::onEnter();
}

void PVEView::onExit()
{
	CCLayer::onExit();
}

bool PVEView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLog("x:%f,y:%f\n", touch->getLocation().x, touch->getLocation().y);
	mCurDrag = Engine::world->getActor(touch->getLocation() - mLayerActor->getPosition());
	if (mCurDrag != NULL && !mCurDrag->isBarrier())
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

void PVEView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if (mCurDrag && mCurDrag->isHero())
	{
		mCurDrag->sprite()->setPosition(touch->getLocation() - mLayerActor->getPosition());
		mRangeSprite->setPosition(touch->getLocation() - mLayerActor->getPosition());
	}
}

void PVEView::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if (mCurDrag && mCurDrag->isHero())
	{

		int x = floor((touch->getLocation().x - mLayerActor->getPositionX() - X_MARGIN) / GRID_SIZE);
		int y = floor((touch->getLocation().y - mLayerActor->getPositionY()) / GRID_SIZE);
		mRangeSprite->setPosition(ccp(x * GRID_SIZE + X_MARGIN + GRID_SIZE / 2, y * GRID_SIZE + GRID_SIZE / 2));
		mCurDrag->sprite()->setPosition(ccp(x * GRID_SIZE + X_MARGIN + GRID_SIZE / 2, y * GRID_SIZE + GRID_SIZE / 2));
		System::pve->moveHero(mCurDrag->getData()->iid, x, y);
	}
}

void PVEView::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{

}