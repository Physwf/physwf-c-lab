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
	setRotation(acos(mDir.x)*180.0/3.14);
	setPosition(ccp(pos.x + mSpeed*mDir.x, pos.y + mSpeed*mDir.y));

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
		effect->mTarget = Engine::scene->getActor(victim)->position();
		effect->setPosition(*Engine::scene->getActor(attacker)->position());
		CCAnimation* anim = ResourceManager::instance()->getAnimation("ice");
		effect->mAction = CCRepeatForever::create(CCAnimate::create(anim));
		return effect;
	}
	return NULL;
}