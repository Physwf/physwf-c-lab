#include "PropSprite.h"
#include "ResourceManager.h"

PropSprite::PropSprite()
{

}

PropSprite::~PropSprite()
{

}

PropSprite* PropSprite::create(ID cid)
{
	PropSprite* pSprite = new PropSprite();
	CCSpriteFrame* frame;
	if (cid == 4001)
		frame = ResourceManager::instance()->getSpriteFrame("golds.png");
	else if (cid == 4002)
		frame = ResourceManager::instance()->getSpriteFrame("blood.png");
	if (pSprite && pSprite->initWithSpriteFrame(frame))
	{
		pSprite->autorelease();
		return pSprite;
	}
	return NULL;
}

