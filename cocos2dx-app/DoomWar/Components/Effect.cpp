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
		Engine::scene->pve()->layerEffect()->removeChild(this, false);
		return true;
	}
	mDir.x = (mTarget->x - pos.x) / dist;
	mDir.y = (mTarget->y - pos.y) / dist;
	float angle = asin(abs(mDir.y))*180.0 / 3.14 ;
	if (mDir.x <= 0 && -mDir.y > 0)//2
	{
		angle += 90.0;
		OutputDebugString(L"90\n");
	}
	else if(mDir.x < 0 && -mDir.y <= 0)//3
	{
		angle += 180.0;
		OutputDebugString(L"180\n");
	}
	else if (mDir.x > 0 && -mDir.y < 0)//4
	{
		angle += 270.0;
		OutputDebugString(L"270\n");
	}
	setRotation(angle + 90.0);
	setPosition(ccp(pos.x + mSpeed*mDir.x, pos.y + mSpeed*mDir.y));
	
	return false;
}

void BulletEffect::fire()
{
	Engine::scene->pve()->layerEffect()->addChild(this);
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
	mAction->release();
	release();
}

BulletEffect* BulletEffect::create(ID cid, ID attacker, ID victim)
{
	CCSprite* layer = Engine::scene->pve()->layerEffect();
	BulletEffect* effect = new BulletEffect(layer);
	if (effect && effect->init())
	{
		effect->autorelease();
		effect->retain();
		effect->mTarget = Engine::scene->getActor(victim)->position();
		effect->setPosition(*Engine::scene->getActor(attacker)->position());
		CCAnimation* anim = ResourceManager::instance()->getAnimation("ice");
		effect->mAction = CCRepeatForever::create(CCAnimate::create(anim));
		effect->mAction->retain();
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
	return false;
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
