#ifndef _STARTER_H
#define _STARTER_H


#include "EventDispatcher.h"
#include <cocoa/CCObject.h>
#include "cocos2d.h"

USING_NS_CC;

class Launcher : public CCObject
{
public:
	Launcher();
	~Launcher();
public:
	static const EType SET_UP_SUCCESS;

	void setup();
private:
	void onUnitSpriteComplete(CCObject* tex);
	void onMapSpriteComplete(CCObject* tex);
	void onSkillSpriteComplete(CCObject* tex);
	void onUISpriteComplete(CCObject* tex);
	void onAllComplete();
};
#endif
