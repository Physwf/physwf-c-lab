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
	mTrace->setPosition(getPosition());
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
	mLayer->addChild(mTrace);
	runAction(mAction);
}

void BulletEffect::onExit()
{
	CCSprite::onExit();
	//mLayer->removeChild(mTrace,true);
	mTrace->stopSystem();//need remove from parent and recycle
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
		effect->mTrace = CCParticleSystemQuad::create("Data/trace.xml");
		effect->mTrace->retain();
		effect->mTrace->setPosition(effect->getPosition());
		effect->mTrace->setEmissionRate(40);
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
	mSpeed = 10;
}

FrisbeeEffect::~FrisbeeEffect()
{
	
}

bool FrisbeeEffect::tick(float delta)
{
	for (char i = 0; i < mNumPaths; i++)
	{
		Path path = mPath->paths[i];

		char nodeX = path.nodes[mCurNode[i] * 2 + 0];
		char nodeY = path.nodes[mCurNode[i] * 2 + 1];
		char nextX = path.nodes[mCurNode[i] * 2 + 2];
		char nextY = path.nodes[mCurNode[i] * 2 + 3];

		float nextPosX = mFrisbee[i]->getPositionX() + mSpeed*mDir[i]->x;
		float nextPosY = mFrisbee[i]->getPositionY() + mSpeed*mDir[i]->y;

		mDir[i]->x = nextX - nodeX;
		mDir[i]->y = nextY - nodeY;

		int dx = nextPosX - nextX * GRID_SIZE;
		int dy = nextPosY - nextY * GRID_SIZE;
		if (dx*mDir[i]->x + dy*mDir[i]->y > 0)
		{
			nextPosX = nextX * GRID_SIZE;
			nextPosY = nextY * GRID_SIZE;
			mCurNode[i]++;
		}

		if (mCurNode[i] + 1 >= path.numNodes)
		{
			mLayer->removeChild(this, true);
			return true;
		}

		mFrisbee[i]->setPosition(ccp(nextPosX, nextPosY));
		mTraces[i]->setPosition(mFrisbee[i]->getPosition()+*mOrigin);

		float dist = sqrt(mDir[i]->x*mDir[i]->x + mDir[i]->y*mDir[i]->y);
		mDir[i]->x = mDir[i]->x / dist;
		mDir[i]->y = mDir[i]->y / dist;
	}
	
	return false;
}

void FrisbeeEffect::fire()
{
	for (char i = 0; i < mNumPaths; i++)
	{
		mCurNode[i] = 0;
		Path path = mPath->paths[i];

		char nodeX = path.nodes[mCurNode[i] * 2 + 0];
		char nodeY = path.nodes[mCurNode[i] * 2 + 1];
		char nextX = path.nodes[mCurNode[i] * 2 + 2];
		char nextY = path.nodes[mCurNode[i] * 2 + 3];
		mDir[i] = new CCPoint(nextX - nodeX, nextY - nodeY);
		float dist = sqrt(mDir[i]->x*mDir[i]->x + mDir[i]->y*mDir[i]->y);
		mDir[i]->x = mDir[i]->x / dist;
		mDir[i]->y = mDir[i]->y / dist;
	}
	mLayer->addChild(this);
}

void FrisbeeEffect::onEnter()
{
	CCSprite::onEnter();
	for (char i = 0; i < mNumPaths; i++)
	{
		addChild(mFrisbee[i]);
		mFrisbee[i]->runAction(mActions[i]);
		mLayer->addChild(mTraces[i]);
	}
	
}

void FrisbeeEffect::onExit()
{
	CCSprite::onExit();
	for (char i = 0; i < mNumPaths; i++)
	{
		mFrisbee[i]->stopAction(mActions[i]);
		mActions[i]->release();
		mFrisbee[i]->removeFromParent();
		mFrisbee[i]->release();
		mTraces[i]->stopSystem();
	}
	
	release();
}

FrisbeeEffect* FrisbeeEffect::create(ID cid, PathGroup* path, const CCPoint* origin)
{
	CCSprite* layer = Engine::world->pve()->layerEffect();
	FrisbeeEffect* effect = new FrisbeeEffect(layer);
	if (effect && effect->init())
	{
		effect->autorelease();
		effect->retain();
		effect->setPosition(*origin);
		effect->mOrigin = origin;
		effect->mPath = path;
		effect->mNumPaths = path->numPaths;
		char szName[10] = { 0 };
		effect->getFrameNameByCID(cid, szName);
		
		for (char i = 0; i < effect->mNumPaths; i++)
		{
			effect->mActions[i] = CCAnimate::create(ResourceManager::instance()->getAnimation(szName));
			effect->mActions[i]->retain();
			effect->mFrisbee[i] = CCSprite::create();
			effect->mFrisbee[i]->retain();
			effect->mTraces[i] = CCParticleSystemQuad::create("Data/fireball.xml");
			effect->mTraces[i]->retain();
		}
		
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


