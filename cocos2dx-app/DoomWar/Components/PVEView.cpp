#include "PVEView.h"
#include "Engine.h"
#include "System.h"

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
	mLayerUI = CCSprite::create();

	this->addChild(mLayerMap);
	this->addChild(mLayerProp);
	this->addChild(mLayerActor);
	this->addChild(mLayerEffect);
	this->addChild(mLayerUI);

	CCTMXTiledMap* map = CCTMXTiledMap::create("./Data/MAPPVE.tmx");
	map->setPosition(-65, 0);
	mLayerMap->addChild(map);

	mPVEUI = PVEUI::create(this);
	mPVEUI->setTouchEnabled(true);
	mLayerUI->addChild(mPVEUI);

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

CCSprite* PVEView::layerUI()
{
	return mLayerUI;
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
	mCurDrag = Engine::world->getActorByGrid(touch->getLocation() - mLayerActor->getPosition());
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