#ifndef _MAPSPRITE_H
#define _MAPSPRITE_H

#include "cocos2d.h"

using namespace cocos2d;

class MapSprite : public CCSprite
{
public:
	MapSprite(unsigned int mid);
	~MapSprite();

	static MapSprite* create(unsigned int mid);
protected:
	
private:
	unsigned int mMid;
	CCSprite* mTempMap;//for temp use
	CCTMXTiledMap* mMap;
};
#endif