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
		Engine::world->pve()->layerEffect()->removeChild(this, false);
		return true;
	}
	setPosition(ccp(pos.x + mSpeed*mDir.x, pos.y + mSpeed*mDir.y));
	
	return false;
}

void BulletEffect::fire()
{
	mLayer->addChild(this);

	CCPoint pos = getPosition();
	float dist = pos.getDistance(*mTarget);

	mDir.x = (mTarget->x - pos.x) / dist;
	mDir.y = (mTarget->y - pos.y) / dist;
	float angle = asin(abs(mDir.y))*180.0 / 3.14;
	if (mDir.x >= 0 && -mDir.y > 0)//1
	{

	}
	else if (mDir.x <= 0 && -mDir.y > 0)//2
	{
		angle = 180.0 - angle;
	}
	else if (mDir.x < 0 && -mDir.y <= 0)//3
	{
		angle = 180.0 + angle;
	}
	else if (mDir.x >= 0 && -mDir.y < 0)//4
	{
		angle = 360.0 - angle;
	}
	setRotation(angle + 90.0);
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
	CCSprite* layer = Engine::world->pve()->layerEffect();
	BulletEffect* effect = new BulletEffect(layer);
	if (effect && effect->init())
	{
		effect->autorelease();
		effect->retain();
		effect->mTarget = Engine::world->getActor(victim)->position();
		effect->setPosition(*Engine::world->getActor(attacker)->position());
		char szName[10] = { 0 };
		effect->getFrameNameByCID(cid, szName);
		CCAnimation* anim = ResourceManager::instance()->getAnimation(szName);
		effect->mAction = CCRepeatForever::create(CCAnimate::create(anim));
		effect->mAction->retain();
		return effect;
	}
	return NULL;
}

void BulletEffect::getFrameNameByCID(ID cid, char* name)
{
	if (cid == SKILL_EFFECT_ARROW)
	{
		sprintf(name, "%s", "arrow");
	}
	else if (cid == SKILL_EFFECT_ICE)
	{
		sprintf(name, "%s", "ice");
	}
	else if (cid == SKILL_EFFECT_DAGGER)
	{
		sprintf(name, "%s", "dagger");
	}
	else if (cid == SKILL_EFFECT_FIREBALL)
	{
		sprintf(name, "%s", "fireball");
	}
}
/*MissileEffect*/
FrisbeeEffect::FrisbeeEffect(CCSprite* layer)
{
	mLayer = layer;
}

FrisbeeEffect::~FrisbeeEffect()
{
	
}

bool FrisbeeEffect::tick(float delta)
{
	return true;
}

void FrisbeeEffect::fire()
{

}

void FrisbeeEffect::onEnter()
{
	CCSprite::onEnter();
	runAction(mAction);
}

void FrisbeeEffect::onExit()
{
	CCSprite::onExit();
	stopAction(mAction);
	mAction->release();
	release();
}

FrisbeeEffect* FrisbeeEffect::create(ID cid, ID attacker)
{
	CCSprite* layer = Engine::world->pve()->layerEffect();
	FrisbeeEffect* effect = new FrisbeeEffect(layer);
	if (effect && effect->init())
	{
		effect->autorelease();
		effect->retain();
		effect->setPosition(*Engine::world->getActor(attacker)->position());
		char szName[10] = { 0 };
		effect->getFrameNameByCID(cid, szName);
		CCAnimation* anim = ResourceManager::instance()->getAnimation(szName);
		effect->mAction = CCAnimate::create(anim);
		effect->mAction->retain();
		return effect;
	}
	return NULL;
}

void FrisbeeEffect::getFrameNameByCID(ID cid, char* name)
{
	if (cid == SKILL_EFFECT_FIREBALL)
	{
		sprintf(name, "%s", "fireball");
	}
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
	return mAction->isDone();
}

void HackEffect::fire()
{
	mLayer->addChild(this);

	CCPoint pos = getPosition();
	float dist = pos.getDistance(*mTarget);

	mDir.x = (mTarget->x - pos.x) / dist;
	mDir.y = (mTarget->y - pos.y) / dist;
	float angle = asin(abs(mDir.y))*180.0 / 3.14;
	if (mDir.x >= 0 && -mDir.y > 0)//1
	{

	}
	else if (mDir.x <= 0 && -mDir.y > 0)//2
	{
		angle = 180.0 - angle;
	}
	else if (mDir.x < 0 && -mDir.y <= 0)//3
	{
		angle = 180.0 + angle;
	}
	else if (mDir.x >= 0 && -mDir.y < 0)//4
	{
		angle = 360.0 - angle;
	}
	setRotation(angle + 90.0);
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
	mAction->release();
	release();
}

HackEffect* HackEffect::create(ID cid, ID attacker, ID victim)
{
	CCSprite* layer = Engine::world->pve()->layerEffect();
	HackEffect* effect = new HackEffect(layer);
	if (effect && effect->init())
	{
		effect->autorelease();
		effect->retain();
		effect->setPosition(*Engine::world->getActor(attacker)->position());
		effect->mTarget = Engine::world->getActor(victim)->position();
		CCAnimation* anim = ResourceManager::instance()->getAnimation("axe");
		effect->mAction = CCAnimate::create(anim);
		effect->mAction->retain();
		return effect;
	}
	return NULL;
}

ArcEffect::ArcEffect(CCSprite* layer)
{
	mLayer = layer;
}

ArcEffect::~ArcEffect()
{

}

bool ArcEffect::tick(float delta)
{
	mTime += delta;
	if (mTime > 0.2f)
	{
		mLayer->removeChild(this,true);
		return true;
	}
	return false;
}

void ArcEffect::fire()
{
	mLayer->addChild(this);
	mTime = 0;
}

void ArcEffect::onEnter()
{

}

void ArcEffect::onExit()
{

}

void ArcEffect::draw()
{
	ccDrawColor4B(255, 255, 255, 255);
	glLineWidth(3);
	CCPoint aPos = mAttacker->sprite()->getPosition();
	CCPoint vPos = mVictim->sprite()->getPosition();
	setPosition(aPos);
	drawArc(0, 0, vPos.x - aPos.x, vPos.y - aPos.y, 100.0f);
}

void ArcEffect::drawArc(float x1,float y1,float x2,float y2,float distance)
{
	if (distance < 5)
	{
		ccDrawLine(ccp(x1,y1),ccp(x2,y2));
	}
	else
	{
		float midx = (x1 + x2) / 2;
		float midy = (y1 + y2) / 2;
		midx += (CCRANDOM_0_1() - .5) * distance;
		midy += (CCRANDOM_0_1() - .5) * distance;
		drawArc(x1, y1, midx, midy, distance / 2);
		drawArc(x2, y2, midx, midy, distance / 2);
	}
}

ArcEffect* ArcEffect::create(ID cid, ID attacker, ID victim)
{
	CCSprite* layer = Engine::world->pve()->layerEffect();
	ArcEffect * arc = new ArcEffect(layer);
	if (arc && arc->init())
	{
		arc->mAttacker = Engine::world->getActor(attacker);
		arc->mVictim = Engine::world->getActor(victim);
		arc->setPosition(arc->mAttacker->sprite()->getPosition());
		return arc;
	}
	return NULL;
}


