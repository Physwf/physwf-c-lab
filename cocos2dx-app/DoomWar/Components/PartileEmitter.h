#ifndef _PARTILE_EMITTER_H
#define _PARTILE_EMITTER_H

#include "cocos2d.h"

USING_NS_CC;

class ParticleTraceEmiter : public CCParticleSystemQuad
{
public:
	ParticleTraceEmiter(CCSprite* layer);
	~ParticleTraceEmiter();
public:
	bool init() { return initWithTotalParticles(10); };
	virtual bool initWithTotalParticles(unsigned int numberOfPartiles);
	static ParticleTraceEmiter* create();
private:
	CCSprite* mLayer;
};
#endif