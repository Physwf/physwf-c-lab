#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include "cocos2d.h"
#include <cocoa\CCObject.h>

using namespace cocos2d;

class ResourceManager
{
public:
	static ResourceManager* instance();

	CCSpriteFrame* getSpriteFrame(const char* name);
	CCAnimationFrame* getAnimationFrame(const char* name);

	void load(const char* pszFile, CCObject* target, SEL_CallFuncO selector);
	void addSpriteFramePack(const char* plist, CCTexture2D *pobTexture);

private:
	ResourceManager();
	~ResourceManager();

private:
	static ResourceManager* mInstance;
	CCSpriteFrameCache* mFrameCache;
	CCAnimationCache* mAnimationCache;
};
#endif