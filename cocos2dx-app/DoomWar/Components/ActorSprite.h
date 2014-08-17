#ifndef _DW_ACTOR_H
#define _DW_ACTOR_H

#include "cocos2d.h"
#include "dwtype.h"

using namespace cocos2d;

#define BLOOD_RENDER_W 100
#define BLOOD_RENDER_H 10

class BloodRender : public CCRenderTexture
{
public:
	BloodRender(unsigned int color);
	~BloodRender();

	static BloodRender* create(unsigned int color);

	void setPercent(float percent);
	
private:
	float mPercent;
	unsigned int mColor;
};

class ActorSprite : public CCSprite
{
public:
	ActorSprite(ID cid);
	~ActorSprite();
	
	static ActorSprite* create(ID cid);

	

	virtual void update(float delta);

private:
	ID mIID;
	ID mCID;

	CCSprite* mBody;
	CCSprite* mDeadBody;
	CCAnimation* mArmor;
	CCSprite* mBloodBar;
	CCLayer* mBloodLayer;
	CCLayer* mEffectLayer;
};
#endif