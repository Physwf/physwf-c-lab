#include "ActorSprite.h"
#include "ResourceManager.h"

ActorSprite::ActorSprite(ID cid)
{

}

ActorSprite::~ActorSprite()
{

}

void ActorSprite::update(float delta)
{

}

ActorSprite* ActorSprite::create(ID cid)
{
	ActorSprite* pActor = new ActorSprite(cid);
	if (pActor && pActor->init())
	{
		pActor->autorelease();
		char strcid[20] = {0};
		getFrameNameByCID(cid,strcid);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(strcid);
		pActor->mBody = CCSprite::createWithSpriteFrame(frame);
		pActor->addChild(pActor->mBody);
		pActor->mBody->setAnchorPoint(ccp(0,0));

		//blood bar
		//armor
		return pActor;
	}
	return NULL;
}

void ActorSprite::getFrameNameByCID(ID cid, char* name)
{
	switch (cid)
	{
	case 1:
	{
			  sprintf(name, "%s", "archer.png");
			  break;
	}
	case 2:
	{
			  sprintf(name, "%s", "BarriersFlower.png");
			  break;
	}
	case 3:
	{
			  sprintf(name, "%s", "gnome.png");
			  break;
	}
	default:
		break;
	}
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




