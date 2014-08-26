#include "Effect.h"
#include "ResourceManager.h"
#include "Engine.h"

BulletEffect::BulletEffect(CCSprite* layer)
{
	mLayer = layer;
	mSpeed = 10.0;
}

BulletEffect::~BulletEffect()
{

}

bool BulletEffect::tick(float delta)
{
	CCPoint pos = getPosition();
	float dist = pos.getDistance(*mTarget);
	if (dist <= mSpeed)
	{
		mLayer->removeChild(this,false);
		return true;
	}
	mDir.x = (mTarget->x - pos.x) / dist;
	mDir.y = (mTarget->y - pos.y) / dist;
	float angle = -asin(mDir.y)*180.0 / 3.14 ;
	if (mDir.x < 0 && mDir.y > 0)
	{
		angle -= 90.0;
	}
	else if(mDir.x < 0 && mDir.y < 0)
	{
		angle += 90.0;
	}
	else if (mDir.x > 0 && mDir.y < 0)
	{
		angle -= 270.0;
	}
	setRotation(angle + 90.0);
	setPosition(ccp(pos.x + mSpeed*mDir.x, pos.y + mSpeed*mDir.y));
	OutputDebugString(L"123\n");
	return false;
}

void BulletEffect::fire()
{
	mLayer->addChild(this);
}

void BulletEffect::onEnter()
{
	CCSprite::onEnter();
	runAction(mAction);
}

void BulletEffect::onExit()
{
	CCSprite::onExit();
	stopAction(mAction);
}

BulletEffect* BulletEffect::create(ID cid, ID attacker, ID victim)
{
	CCSprite* layer = Engine::scene->pve()->layerEffect();
	BulletEffect* effect = new BulletEffect(layer);
	if (effect && effect->init())
	{
		effect->autorelease();
		effect->mTarget = Engine::scene->getActor(victim)->position();
		effect->setPosition(*Engine::scene->getActor(attacker)->position());
		CCAnimation* anim = ResourceManager::instance()->getAnimation("ice");
		effect->mAction = CCRepeatForever::create(CCAnimate::create(anim));
		return effect;
	}
	return NULL;
}

HackEffect::HackEffect(CCSprite* layer)
{
	mLayer = layer;
}

HackEffect::~HackEffect()
{

}

bool HackEffect::tick(float delta)
{

}

void HackEffect::fire()
{
	mLayer->addChild(this);
}

void HackEffect::onEnter()
{
	CCSprite::onEnter();
	runAction(mAction);
}

void HackEffect::onExit()
{
	CCSprite::onEnter();
	stopAction(mAction);
}

HackEffect* HackEffect::create(ID cid, ID attacker, ID victim)
{
	CCSprite* layer = Engine::scene->pve()->layerEffect();
	HackEffect* effect = new HackEffect(layer);
	if (effect && effect->init())
	{
		effect->autorelease();
		CCAnimation* anim = ResourceManager::instance()->getAnimation("axe");
		effect->mAction = CCAnimate::create(anim);
		return effect;
	}
	return NULL;
}
