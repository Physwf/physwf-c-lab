#include "ActorSprite.h"
#include "ResourceManager.h"

ActorSprite::ActorSprite(unsigned int cid)
{

}

ActorSprite::~ActorSprite()
{

}

void ActorSprite::update(float delta)
{

}

ActorSprite* ActorSprite::create(unsigned int cid)
{
	ActorSprite* pActor = new ActorSprite(cid);
	if (pActor && pActor->init())
	{
		pActor->autorelease();
		char strcid[10];
		sprintf(strcid, "%s", cid);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(strcid);
		pActor->mBody = CCSprite::createWithSpriteFrame(frame);
		pActor->addChild(pActor->mBody);

		//blood bar
		//armor
		return pActor;
	}
	return NULL;
}


BloodRender::BloodRender(unsigned int color)
{
	mColor = color;
	mPercent = 1.0;
}

BloodRender::~BloodRender()
{

}

BloodRender* BloodRender::create(unsigned int color)
{
	BloodRender* pBloor = new BloodRender(color);
	if (pBloor && pBloor->init())
	{
		return pBloor;
	}
	return NULL;
}

void BloodRender::setPercent(float percent)
{
	mPercent = percent;
	this->begin();
	this->clear(0, 0, 0, 1);

	this->end();
}




