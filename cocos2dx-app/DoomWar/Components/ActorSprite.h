#ifndef _DW_ACTOR_H
#define _DW_ACTOR_H

#include "cocos2d.h"
#include "dwtype.h"
#include "Unit.h"

using namespace cocos2d;

#define BLOOD_RENDER_W 100
#define BLOOD_RENDER_H 10
#define GRID_SIZE 96.0

class BloodBar : public CCSprite
{
public:
	~BloodBar();

	static BloodBar* create(float percent);

	void setPercent(float percent);
	void setDelta(float delta);
private:
	BloodBar(float percent);
private:
	float mPercent;
	unsigned int mPixels[96*8];
	CCTexture2D *mTexture;
};

class ActorSprite : public CCSprite
{
public:
	ActorSprite(ID cid);
	~ActorSprite();
	
	static ActorSprite* create(ID cid);
	static void getFrameNameByCID(ID cid,char* name);
	
	BloodBar* bloor() const;
	virtual void update(float delta);

private:
	ID mIID;
	ID mCID;

	CCSprite* mBody;
	CCSprite* mDeadBody;
	CCAnimation* mArmor;
	BloodBar* mBloodBar;
	CCLayer* mBloodLayer;
	CCLayer* mEffectLayer;
};

class ColorSprite : public CCSprite
{
public:
	ColorSprite();
	~ColorSprite();

	static ColorSprite* create(unsigned int color);

	void updateData(Unit* unit);
private:
	CCTexture2D* mColorTex;
	std::vector<CCSprite*> mSprites;
};

#endif