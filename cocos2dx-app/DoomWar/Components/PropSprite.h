#ifndef _PROP_SPRITE_H
#define _PROP_SPRITE_H

#include "cocos2d.h"
#include "dwtype.h"
using namespace cocos2d;

class PropSprite : public CCSprite
{
public:
	PropSprite();
	~PropSprite();

	static PropSprite* create(ID cid);

};
#endif