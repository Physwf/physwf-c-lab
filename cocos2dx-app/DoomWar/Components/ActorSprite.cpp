#include "ActorSprite.h"
#include "ResourceManager.h"

ActorSprite::ActorSprite(ID cid)
{

}

ActorSprite::~ActorSprite()
{

}

void ActorSprite::update(float delta)
{

}

ActorSprite* ActorSprite::create(ID cid)
{
	ActorSprite* pActor = new ActorSprite(cid);
	if (pActor && pActor->init())
	{
		pActor->autorelease();
		char strcid[20] = {0};
		getFrameNameByCID(cid,strcid);
		CCSpriteFrame* frame = ResourceManager::instance()->getSpriteFrame(strcid);
		pActor->mBody = CCSprite::createWithSpriteFrame(frame);
		pActor->addChild(pActor->mBody);
		//pActor->mBody->setAnchorPoint(ccp(0,0));
		pActor->mBloodBar = BloodBar::create(100);
		//pActor->mBloodBar->setAnchorPoint(ccp(0, 0));
		pActor->mBloodBar->setPosition(ccp(0, -pActor->mBody->getContentSize().height / 2));
		pActor->addChild(pActor->mBloodBar);
		//blood bar
		//armor
		return pActor;
	}
	return NULL;
}

void ActorSprite::getFrameNameByCID(ID cid, char* name)
{
	switch (cid)
	{
		case 1001:
			sprintf(name, "%s", "soldier.png");
			break;
		case 1002:
			sprintf(name, "%s", "archer.png");
			break;
		case 1003:
			sprintf(name, "%s", "Warlock.png");
			break;
		case 1004:
			sprintf(name, "%s", "assassin.png");
			break;
		case 1005:
			sprintf(name, "%s", "wizard.png");
			break;
		case 1006:
			sprintf(name, "%s", "oxe.png");
			break;
		case 2001:
			sprintf(name, "%s", "gnome.png");
			break;
		case 3001:
			sprintf(name, "%s", "BarriersFlower.png");
			break;
		default:
			break;
	}
}

BloodBar* ActorSprite::bloor() const
{
	return mBloodBar;
}

BloodBar::BloodBar(float percent)
{
	mTexture = new CCTexture2D();
	setPercent(percent);
	memset(mPixels, 0, sizeof(mPixels)); 
}

BloodBar::~BloodBar()
{

}

BloodBar* BloodBar::create(float percent)
{
	BloodBar* pBloor = new BloodBar(percent);
	if (pBloor && pBloor->initWithTexture(pBloor->mTexture))
	{
		pBloor->autorelease();
		return pBloor;
	}
	return NULL;
}

void BloodBar::setPercent(float percent)
{
	mPercent = (percent<0.0f) ? 0.0f : (percent>100.0f ? 100.0f : percent);
	float n = mPercent / 100.0f;
	unsigned int g = (float)0xFF * n;
	unsigned int r = (float)0xFF * (1.0 - n);
	unsigned int color = (g << 8) + (r);
	std::fill_n(mPixels, 96, 0xFF000000);
	color += 0xFF000000;
	std::fill_n(mPixels, 96 * n, color);
	for (int i = 1; i < 8; i++)
	{
		memcpy(mPixels + 96 * i, mPixels, 96 * sizeof(unsigned int));
	}
	CCSize size(96, 8);
	mTexture->initWithData((const void*)&mPixels, kCCTexture2DPixelFormat_RGBA8888, 96, 8, size);
}

void BloodBar::setDelta(float delta)
{
	setPercent(mPercent + delta);
}

ColorSprite::ColorSprite()
{
	
}

ColorSprite::~ColorSprite()
{

}

ColorSprite* ColorSprite::create(unsigned int color)
{
	ColorSprite* pSprite = new ColorSprite();
	if (pSprite && pSprite->init())
	{
		pSprite->mColorTex = new CCTexture2D();
		pSprite->mColorTex->retain();
		CCSize size(GRID_SIZE, GRID_SIZE);
		pSprite->mColorTex->initWithData(&color, kCCTexture2DPixelFormat_RGBA8888, 1, 1, size);
		
		pSprite->autorelease();
		return pSprite;
	}
	return NULL;
}

void ColorSprite::updateData(Unit* unit)
{
	int i = 0;
	int size = mSprites.size();
	for (i; i < mSprites.size(); i++)
	{
		mSprites[i]->removeFromParent();
	}
	Skill skill;
	Config::skill->fill(&skill, unit->skills[0]);
	for (i = 0; i < skill.range.numGrids; i++)
	{
		CCSprite* tile;
		if (i<size)
			tile = mSprites[i];
		else
		{
			tile = CCSprite::createWithTexture(mColorTex);
			tile->retain();
			mSprites.push_back(tile);
		}		
		addChild(tile);
		tile->setPosition(ccp(skill.range.offsets[i].x * GRID_SIZE, skill.range.offsets[i].y * GRID_SIZE));
	}
	for (i; i < size; i++)
	{
		mSprites[i]->removeFromParent();
	}
}
