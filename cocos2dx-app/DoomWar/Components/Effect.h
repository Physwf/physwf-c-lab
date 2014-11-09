#ifndef _EFFECT_H
#define _EFFECT_H

#include "cocos2d.h"
#include "dwtype.h"
#include "Actor.h"

using namespace cocos2d;

class Effect : public CCSprite
{
public:
	virtual bool tick(float delta) = 0;
	virtual void fire() = 0;
protected:
	CCSprite* mLayer;
};

class BulletEffect : public Effect
{
public:
	virtual bool tick(float delta);
	virtual void fire();
	virtual void onEnter();
	virtual void onExit();
	static BulletEffect* create(ID cid, ID attacker, ID victim);
private:
	BulletEffect(CCSprite* layer);
	~BulletEffect();

	void getFrameNameByCID(ID cid, char* name);
private:
	CCAction* mAction;
	CCPoint* mTarget;
	float mSpeed;
	CCPoint mDir;
	CCParticleSystemQuad* mTrace;
	CCParticleSystemQuad* mHitEmitter;
};

class FrisbeeEffect : public Effect
{
public:
	virtual bool tick(float delta);
	virtual void fire();
	virtual void onEnter();
	virtual void onExit();
	void addTarget(ID iid);
	static FrisbeeEffect* create(ID cid, PathGroup* path, const CCPoint* origin);
private:
	FrisbeeEffect(CCSprite* layer);
	~FrisbeeEffect();

	void getFrameNameByCID(ID cid, char* name);
private:
	CCParticleSystemQuad* mTraces[MAX_NUM_PATHS];
	CCSprite* mFrisbee[MAX_NUM_PATHS];
	CCAnimate* mActions[MAX_NUM_PATHS];
	float mSpeed;
	const CCPoint* mOrigin;
	CCPoint* mDir[MAX_NUM_PATHS];
	PathGroup* mPath;
	char mCurNode[MAX_NUM_PATHS];
	char mNumPaths;
	std::vector<Actor*> mTargets;
};

class HackEffect : public Effect
{
public:
	virtual bool tick(float delta);
	virtual void fire();
	virtual void onEnter();
	virtual void onExit();
	static HackEffect* create(ID cid, ID attacker, ID victim);
private:
	HackEffect(CCSprite* layer);
	~HackEffect();
private:
	CCAction* mAction;
	CCPoint mDir;
	CCPoint* mTarget;
};

class ArcEffect : public Effect
{
public:
	virtual bool tick(float delta);
	virtual void fire();
	virtual void draw();
	virtual void onEnter();
	virtual void onExit();
	void drawArc(float x1, float y1, float x2, float y2, float distance);
	static ArcEffect* create(ID cid, ID attacker, ID victim);
private:
	ArcEffect(CCSprite* layer);
	~ArcEffect();
private:
	CCAction* mAction;
	Actor* mAttacker;
	Actor* mVictim;
	float mTime;
};
#endif
