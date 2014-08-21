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
		pActor->mBloodBar = BloodRender::create(0.3);
		pActor->mBloodBar->setAnchorPoint(ccp(0, 0));
		pActor->addChild(pActor->mBloodBar);
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

BloodRender::BloodRender(float percent)
{
	mTexture = new CCTexture2D();
	mPercent = percent;
	unsigned int prog = percent * 100;
	float n  =  prog / 100.0;
	float p  = n - floor(n);
	unsigned int temp1 = 0xFF * (1.0 - p);
	unsigned int temp2 = 0xFF * p;
	unsigned int color = (temp1 << 16) + (temp2 << 8);
	color += 0xFF000000;
	//unsigned int color = 0xFF00FF00;
	CCSize size(96, 8);
	mTexture->initWithData((const void*)&color, kCCTexture2DPixelFormat_RGBA8888, 1, 1, size);
}

BloodRender::~BloodRender()
{

}

BloodRender* BloodRender::create(float percent)
{
	BloodRender* pBloor = new BloodRender(percent);
	if (pBloor && pBloor->initWithTexture(pBloor->mTexture))
	{
		pBloor->autorelease();
		return pBloor;
	}
	return NULL;
}

void BloodRender::setPercent(float percent)
{
	mPercent = percent;
	CCSize size(100, 8);
	unsigned int color = 0xFF00FF00;
	mTexture->initWithData((const void*)&color, kCCTexture2DPixelFormat_RGBA8888, 1, 1, size);
}




