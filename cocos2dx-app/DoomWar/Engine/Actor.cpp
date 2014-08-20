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
	mLayer->addChild(mSprite);
}

ID Actor::iid() const
{
	return mData->iid;
}

void Actor::stepForword()
{
	mSprite->setPositionY(mData->positon.y * GRID_SIZE);
}


