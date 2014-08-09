#include "MapSprite.h"

MapSprite::MapSprite(unsigned int mid)
{
	mMid = mid;
}

MapSprite::~MapSprite()
{

}

MapSprite* MapSprite::create(unsigned int mid)
{
	MapSprite* pMap = new MapSprite(mid);
	if (pMap && pMap->init())
	{
		pMap->mTempMap = CCSprite::create("./Data/single.png");
		pMap->addChild(pMap->mTempMap);
	}
}

