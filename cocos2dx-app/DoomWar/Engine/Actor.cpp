#include "Actor.h"

Actor::Actor(CCLayer* layer)
{
	mLayer = layer;
}

void Actor::setData(Unit* data)
{
	mData = data;
	mSprite = ActorSprite::create(mData->cid);
	mSprite->setPosition(ccp(mData->positon.x * 93, mData->positon.y * 93));
	mLayer->addChild(mSprite);
}

ID Actor::iid() const
{
	return mData->iid;
}



