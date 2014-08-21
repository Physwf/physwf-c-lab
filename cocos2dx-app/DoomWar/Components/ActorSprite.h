#ifndef _DW_ACTOR_H
#define _DW_ACTOR_H

#include "cocos2d.h"
#include "dwtype.h"

using namespace cocos2d;

#define BLOOD_RENDER_W 100
#define BLOOD_RENDER_H 10

class BloodRender : public CCSprite
{
public:
	~BloodRender();

	static BloodRender* create(float percent);

	void setPercent(float percent);
private:
	BloodRender(float percent);
private:
	float mPercent;
	CCTexture2D *mTexture;
};

class ActorSprite : public CCSprite
{
public:
	ActorSprite(ID cid);
	~ActorSprite();
	
	static ActorSprite* create(ID cid);
	static void getFrameNameByCID(ID cid,char* name);
	

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