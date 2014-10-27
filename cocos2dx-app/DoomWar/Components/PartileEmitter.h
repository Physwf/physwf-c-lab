#ifndef _PARTILE_EMITTER_H
#define _PARTILE_EMITTER_H

#include "cocos2d.h"

USING_NS_CC;

class ParticleTraceEmitter : public CCParticleSystemQuad
{
public:
	ParticleTraceEmitter(CCSprite* layer);
	~ParticleTraceEmitter();
public:
	bool init() { return initWithTotalParticles(100); };
	virtual bool initWithTotalParticles(unsigned int numberOfPartiles);
	static ParticleTraceEmitter* create();
private:
	CCSprite* mLayer;
};

class ParticleHitEmitter : public CCParticleSystemQuad
{
public:
	ParticleHitEmitter(CCSprite* layer);
	~ParticleHitEmitter();
public:
	bool init() { return initWithTotalParticles(10); };
	virtual bool initWithTotalParticles(unsigned int numberOfPartiles);
	static ParticleHitEmitter* create();
private:
	CCSprite* mLayer;
};

class ParticleIceBallEmitter : public CCParticleSystemQuad
{
public:
	ParticleIceBallEmitter(CCSprite* layer);
	~ParticleIceBallEmitter();
public:
	bool init() { return initWithTotalParticles(10); };
	virtual bool initWithTotalParticles(unsigned int numberOfPartiles);
	static ParticleIceBallEmitter* create();
private:
	CCSprite* mLayer;
};
#endif