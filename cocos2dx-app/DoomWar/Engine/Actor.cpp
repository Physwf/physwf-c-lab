#include "Actor.h"

Actor::Actor(CCLayer* layer)
{
	mLayer = layer;
}

void Actor::setData(Unit* data)
{
	mData = data;
	mSprite = ActorSprite::create(mData->cid);
	mSprite->setPosition(ccp(300, 300));
	mLayer->addChild(mSprite);
}

ID Actor::iid() const
{
	return mData->iid;
}



