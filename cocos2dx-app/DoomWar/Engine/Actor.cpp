#include "Actor.h"

Actor::Actor(CCLayer* layer)
{
	mLayer = layer;
}

void Actor::setData(Unit* data)
{
	mData = data;
	mSprite = ActorSprite::create(mData->cid);
	mSprite->setPosition(ccp(mData->positon.x * GRID_SIZE + X_MARGIN, mData->positon.y * GRID_SIZE));
	//mSprite->bloor()->setPercent((float)mData->health / (float)mData->maxHealth);
	mLayer->addChild(mSprite);
}

ID Actor::iid() const
{
	return mData->iid;
}

void Actor::updatePosition()
{
	mSprite->setPosition(ccp(mData->positon.x * GRID_SIZE + X_MARGIN, mData->positon.y * GRID_SIZE));
}

void Actor::updateHealth(int delta)
{
	mSprite->bloor()->setPercent((float)mData->health / (float)mData->maxHealth);
}


